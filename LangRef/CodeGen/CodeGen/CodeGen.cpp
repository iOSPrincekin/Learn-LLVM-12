//
//  CodeGen.cpp
//  Calc
//
//  Created by LEE on 7/10/22.
//

#include "CodeGen.hpp"
#include <iostream>

using namespace llvm;

namespace{
class ToIRVisitor {
    Module *M;
    IRBuilder<> Builder;
    Type *VoidTy;
    Type *Int8Ty;
    Type *Int32Ty;
    Type *Int64Ty;
    PointerType *Int8PtrTy;
    PointerType *Int32PtrTy;
    PointerType *Int8PtrPtrTy;
    Constant *Int32Zero;
    
    GlobalVariable *TypeInfo = nullptr;
    FunctionType *AllocEHFty = nullptr;
    Function *AllocEHFn = nullptr;
    FunctionType *ThrowEHFty = nullptr;
    Function *ThrowEHFn = nullptr;
    BasicBlock *LPadBB = nullptr;
    BasicBlock *UnreachableBB = nullptr;
    
    Value *V;
    StringMap<Value *> nameMap;
    
public:
    ToIRVisitor(Module *M) : M(M),Builder(M->getContext())
    {
    VoidTy = Type::getVoidTy(M->getContext());
    Int8Ty = Type::getInt8Ty(M->getContext());
    Int32Ty = Type::getInt32Ty(M->getContext());
    Int64Ty = Type::getInt64Ty(M->getContext());
    Int8PtrTy = PointerType::get(Int8Ty, 0);
    Int32PtrTy = Type::getInt32PtrTy(M->getContext());
    Int8PtrPtrTy = Int8PtrTy->getPointerTo();
    Int32Zero = ConstantInt::get(Int32Ty, 0,true);
    
    TypeInfo = nullptr;
    AllocEHFty = nullptr;
    AllocEHFn = nullptr;
    ThrowEHFty = nullptr;
    ThrowEHFn = nullptr;
    }
    void run()
    {
    FunctionType *MainFty =
    FunctionType::get(Int32Ty, {Int32Ty, Int8PtrPtrTy}, false);
    Function *MainFn =
    Function::Create(MainFty, GlobalValue::ExternalLinkage, "main", M);
    BasicBlock *BB = BasicBlock::Create(M->getContext(), "entry", MainFn);
    Builder.SetInsertPoint(BB);
    
    
    
    FunctionType *CalcWriteFnTy = FunctionType::get(VoidTy, {Int32Ty}, false);
    Function *CalcWriteFn = Function::Create(
                                             CalcWriteFnTy, GlobalValue::ExternalLinkage, "calc_write", M);
    

    Value*Left = ConstantInt::get(Int32Ty, 3, true);
    
    //     Tree->accept(*this);
    StringRef Var = "a";
    
    FunctionType *ReadFty = FunctionType::get(Int32Ty, {Int8PtrTy}, false);
    Function *ReadFn =
    Function::Create(ReadFty, GlobalValue::ExternalLinkage, "calc_read", M);
    
    Value *Ptr = Builder.CreateGlobalStringPtr(Var,Twine(Var).concat(".str"),0,M);
    CallInst *Call = Builder.CreateCall(ReadFty, ReadFn,{Ptr});
    Value*Right = Call;
    addThrow(42); // Arbitrary payload

    V = Builder.CreateSDiv(Left, Right);
    Builder.CreateCall(CalcWriteFnTy, CalcWriteFn, {V});
    
    Builder.CreateRet(Int32Zero);
    }
    
    void createICmpEq(Value *Left,Value *Right,BasicBlock *&TrueDest,
                      BasicBlock *&FalseDest, const Twine &TrueLabel = "",
                      const Twine &FalseLabel = "")
    {
    Function *Fn = Builder.GetInsertBlock()->getParent();
    TrueDest = BasicBlock::Create(M->getContext(),TrueLabel,Fn);
    FalseDest = BasicBlock::Create(M->getContext(),FalseLabel,Fn);
    Value *Cmp = Builder.CreateCmp(CmpInst::ICMP_EQ, Left, Right);
    Builder.CreateCondBr(Cmp, TrueDest, FalseDest);
    }
    
    void createFunc(FunctionType *&Fty,Function *&Fn,const Twine &N,Type *Result,ArrayRef<Type *>Params = None,bool isVarArgs = false)
    {
    Fty = FunctionType::get(Result, Params, isVarArgs);
    Fn = Function::Create(Fty, GlobalVariable::ExternalLinkage, N,M);
    }
    
    void addThrow(int PayloadVal) {
        if (!TypeInfo) {
            TypeInfo =
            new GlobalVariable(*M, Int8PtrTy,
                               /*isConstant=*/true, GlobalValue::ExternalLinkage,
                               /*Initializer=*/nullptr, "_ZTIi");
            
            // Declare the __cxa_allocate_exception function.
            createFunc(AllocEHFty, AllocEHFn, "__cxa_allocate_exception", Int8PtrTy,
                       {Int64Ty});
            
            // Declare the __cxa_throw function.
            createFunc(ThrowEHFty, ThrowEHFn, "__cxa_throw", VoidTy,
                       {Int8PtrTy, Int8PtrTy, Int8PtrTy});
            
            // Declare personality function.
            FunctionType *PersFty;
            Function *PersFn;
            createFunc(PersFty, PersFn, "__gxx_personality_v0", Int32Ty, None, true);
            
            // Attach personality function to main()
            Function *Fn = Builder.GetInsertBlock()->getParent();
            Fn->setPersonalityFn(PersFn);
            
            // Create and populate the landingpad block and
            // the resume block.
            BasicBlock *SaveBB = Builder.GetInsertBlock();
            LPadBB = BasicBlock::Create(M->getContext(), "lpad", Fn);
            Builder.SetInsertPoint(LPadBB);
            addLandingPad();
            
            UnreachableBB = BasicBlock::Create(M->getContext(), "unreachable", Fn);
            Builder.SetInsertPoint(UnreachableBB);
            Builder.CreateUnreachable();
            
            Builder.SetInsertPoint(SaveBB);
        }
        
        // The size of the payload is 4 byte.
        Constant *PayloadSz = ConstantInt::get(Int64Ty, 4, false);
        
        // Call the function.
        CallInst *EH = Builder.CreateCall(AllocEHFty, AllocEHFn, {PayloadSz});
        
        // Store the payload value.
        Value *PayloadPtr = Builder.CreateBitCast(EH, Int32PtrTy);
        Builder.CreateStore(ConstantInt::get(Int32Ty, PayloadVal, true),
                            PayloadPtr);
        
        // Raise the exception with a call to __cxa_throw
        // function
        Builder.CreateInvoke(ThrowEHFty, ThrowEHFn, UnreachableBB, LPadBB,
                             {EH, ConstantExpr::getBitCast(TypeInfo, Int8PtrTy),
            ConstantPointerNull::get(Int8PtrTy)});
    }
    
    void addLandingPad() {
        assert(TypeInfo && "TypeInfo should be not null");
        
        FunctionType *TypeIdFty;
        Function *TypeIdFn;
        createFunc(TypeIdFty, TypeIdFn, "llvm.eh.typeid.for", Int32Ty, {Int8PtrTy});
        
        FunctionType *BeginCatchFty;
        Function *BeginCatchFn;
        createFunc(BeginCatchFty, BeginCatchFn, "__cxa_begin_catch", Int8PtrTy,
                   {Int8PtrTy});
        
        FunctionType *EndCatchFty;
        Function *EndCatchFn;
        createFunc(EndCatchFty, EndCatchFn, "__cxa_end_catch", VoidTy);
        
        FunctionType *PutsFty;
        Function *PutsFn;
        createFunc(PutsFty, PutsFn, "puts", Int32Ty, {Int8PtrTy});
        
        LandingPadInst *Exc =
        Builder.CreateLandingPad(StructType::get(Int8PtrTy, Int32Ty), 1, "exc");
        Exc->addClause(ConstantExpr::getBitCast(TypeInfo, Int8PtrTy));
        Value *Sel = Builder.CreateExtractValue(Exc, {1}, "exc.sel");
        CallInst *Id = Builder.CreateCall(
                                          TypeIdFty, TypeIdFn, {ConstantExpr::getBitCast(TypeInfo, Int8PtrTy)});
        
        BasicBlock *TrueDest, *FalseDest;
        createICmpEq(Sel, Id, TrueDest, FalseDest, "match", "resume");
        Builder.SetInsertPoint(FalseDest);
        Builder.CreateResume(Exc);
        Builder.SetInsertPoint(TrueDest);
        Value *Ptr = Builder.CreateExtractValue(Exc, {0}, "exc.ptr");
        Builder.CreateCall(BeginCatchFty, BeginCatchFn, {Ptr});
        
        Value *MsgPtr =
        Builder.CreateGlobalStringPtr("Divide by zero!", "msg", 0, M);
        Builder.CreateCall(PutsFty, PutsFn, {MsgPtr});
        Builder.CreateCall(EndCatchFty, EndCatchFn);
        Builder.CreateRet(Int32Zero);
    }
};
    
} // namespace

void CodeGen::compile(){
    LLVMContext Ctx;
    Module *M = new Module("calc.expr",Ctx);
    ToIRVisitor ToIR(M);
    ToIR.run();
    M->print(outs(), nullptr);
}

// 1.创建module
Module* CodeGen::createLLVMSumModule(){
    LLVMContext context;
    Module *module = new Module("haoyuTestLLVMIR",context);
    { //设置datalayout和三元组
        module ->setDataLayout("e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
        module ->setTargetTriple("x86_64-apple-macosx10.14.0");
    }
    
    // 2.创建函数的类型（指定返回值类型、参数类型及数量、是否有可变参数）
    SmallVector<Type *, 2>FunctionArgs;
    // 各种类型都是通过get方法来构造对应的实例
    FunctionArgs.push_back(IntegerType::get(module->getContext(), 32));
    FunctionArgs.push_back(IntegerType::get(module->getContext(), 32));
    
    IntegerType *returnType = IntegerType::get(module->getContext(), 32);
    FunctionType *funcType = FunctionType::get(returnType, FunctionArgs, false);
    
    // 3.创建一个函数
    // LinkageType 是globalValue 类下的一个链接类型，所有全局变量、函数都有一个链接类型
    // GlobalValue::ExternalLinkage 表示该函数可以被其他模块引用
    Function *customFunc = Function::Create(funcType, GlobalVariable::ExternalLinkage, "haoyuSum",module);
    customFunc->setCallingConv(CallingConv::C); // CallingConv 类是一个枚举类，定义了所有的函数调用公约！文档上有说明
    
    
    //4. 存储参数（获取参数的引用）
    Function::arg_iterator argsIT = customFunc->arg_begin();
    Value *param1 = argsIT++;
    param1->setName("a");
    
    Value *param2 = argsIT++;
    param2->setName("b");
    
    // 5.创建基本块（需要定制其所属的function）
    BasicBlock *entryBlock = BasicBlock::Create(module->getContext(),"entry",customFunc,0);
    
    // 6.添加指令，两种方式：1.直接使用具体的指令 2.使用IRBuilder
    // 6.1 直接使用指令方式（便于呈现原始接口）
    // 指令：alloca指令使用（操作变量必须用到指针，同OC是一个道理）
    AllocaInst *ptrA = new AllocaInst(/*要创建的内存空间类型*/IntegerType::get(module->getContext(), 32),/*地址空间*/module->getDataLayout().getAllocaAddrSpace(),/*名称*/"a.addr",/*BasicBlock*/entryBlock);
    ptrA->setAlignment(Align(4)); // 4字节对齐的32位元素
    
    AllocaInst *ptrB = new AllocaInst(/*要创建的内存空间的类型*/ IntegerType::get(module->getContext(), 32),/*地址空间*/module->getDataLayout().getAllocaAddrSpace(),/*名称*/"a.addr",/*BasicBlock*/entryBlock);
    ptrB->setAlignment(Align(4));
    
    //7.使用store指令
    StoreInst *st0 = new StoreInst(param1,ptrA,/* 指定是否是静态存储区 */false,entryBlock);
    st0->setAlignment(Align(4));
    StoreInst *st1 = new StoreInst(param2,ptrB,/* 指定是否为静态存储区*/false,entryBlock);
    st1->setAlignment(Align(4));
    
    //8.使用load命令
    LoadInst *ld0 = new LoadInst(/*类型*/IntegerType::get(context, 32),ptrA,/*名称*/"",false,entryBlock);
    ld0->setAlignment(Align(4));
    LoadInst *ld1 = new LoadInst(/*类型*/IntegerType::get(context, 32),ptrB,/*名称*/"",false,entryBlock);
    ld1->setAlignment(Align(4));
    
    //9.添加操作
    BinaryOperator *addRes = BinaryOperator::Create(Instruction::Add, ld0, ld1,"add",entryBlock);
    //10.设置返回值
    ReturnInst::Create(module->getContext(),addRes,entryBlock);
    
    //11.校验生成的IR
    bool Result = llvm::verifyModule(*module);
    if (Result) {
        std::cout << "IR校验通过" << std::endl;
    }
    module->dump();

    return module;
}

Module* CodeGen::createLLVMWhileModule()
{
    LLVMContext context;
    Module *module = new Module("haoyuWhile",context);
    IRBuilder<> builder(context);
    
    //2、创建main函数
    FunctionType *ft = FunctionType::get(builder.getInt32Ty(),false);
    Function *mainFunc = Function::Create(ft, Function::ExternalLinkage, "_main", module);
    // 创建最外层函数的basic
    BasicBlock *mainEntryBlock = BasicBlock::Create(module->getContext(),"entry",mainFunc,0);
    

    
    // 创建void 函数
    FunctionType *funcType = FunctionType::get(builder.getVoidTy(),false);
    Function *customFunc = Function::Create(funcType, Function::ExternalLinkage, "whileTest",module);
    // 创建最外层函数的basic
    BasicBlock *entryBlock = BasicBlock::Create(module->getContext(),"entry",customFunc,0);
    // 创建br用的basicblock
    BasicBlock *BB1 = BasicBlock::Create(module->getContext(),"label1",customFunc,0);
    BasicBlock *BB2 = BasicBlock::Create(module->getContext(),"label2",customFunc,0);
    BasicBlock *BB3 = BasicBlock::Create(module->getContext(),"label3",customFunc,0);
    // 添加Instruction
    // 1) alloca指令
    AllocaInst *ptr1 = new AllocaInst(/*要创建的内存空间类型*/IntegerType::get(module->getContext(), 32),/*地址空间*/module->getDataLayout().getAllocaAddrSpace(),/*名称*/"1",/*BasicBlock*/entryBlock);
    AllocaInst *ptr2 = new AllocaInst(builder.getInt32Ty(),module->getDataLayout().getAllocaAddrSpace(),"2",entryBlock);
    AllocaInst *ptr3 = new AllocaInst(builder.getInt32Ty(),module->getDataLayout().getAllocaAddrSpace(),"3",entryBlock);
    // 2) store 指令
    auto *IntType = builder.getInt32Ty();
    StoreInst *st1 = new StoreInst(ConstantInt::get(IntType, 0  ),ptr1,entryBlock);
    StoreInst *st2 = new StoreInst(ConstantInt::get(IntType, 10),ptr2,entryBlock);
    StoreInst *st3 = new StoreInst(ConstantInt::get(IntType, 20),ptr3,false,entryBlock);
    
    //3) br指令
    BranchInst::Create(BB1,entryBlock);
    
    // 2.1)设置BB1
    //load 指令
    LoadInst *load1 = new LoadInst(IntegerType::get(context, 32),ptr3,/*名称*/"",false,BB1);
    //icmp指令
    ICmpInst *icmp = new ICmpInst(*BB1,ICmpInst::ICMP_SLT,load1,ConstantInt::get(IntType,10));
    // br
    BranchInst::Create(BB2,BB3,icmp,BB1);
    
    //2.2)设置BB2
    // load指令
    LoadInst *load8 = new LoadInst(IntegerType::get(context, 32),ptr3,/*名称*/"",false,BB2);
    Instruction *add9 = BinaryOperator::Create(Instruction::Add, load8, ConstantInt::get(IntType, 1),"add",BB2);
    StoreInst *stBB2 = new StoreInst(add9,ptr3,BB2);
    LoadInst *load10 = new LoadInst(IntegerType::get(context, 32),ptr2,/*名称*/"",false,BB2);
    Instruction *mul11 = BinaryOperator::Create(Instruction::Mul, load10, ConstantInt::get(IntType, 2),"MUL",BB2);
    StoreInst *stBB3 = new StoreInst(mul11,ptr2,BB2);
    BranchInst::Create(BB1,entryBlock);
    
    //
    //2.3)设置BB3
    ReturnInst::Create(context,ConstantInt::get(IntType, 0),BB3);
    
    ArrayRef<Value *> Args;
    
    CallInst *Call = CallInst::Create(customFunc,Args,"",mainEntryBlock);
    
    module->dump();
    
    return module;
}

Module* createIRWithIRBuilder()
{
    LLVMContext Context;
    Module *mod = new Module("sum.ll",Context);
    
    // 1.创建IRBuilder
    IRBuilder<> builder(Context);
    // 2.创建main函数
    FunctionType *ft = FunctionType::get(builder.getInt32Ty(), false);
    Function *mainfunc = Function::Create(ft, Function::ExternalLinkage, "main",mod);
    // 到此为止创建了main函数，但是函数体内的包含的Instruction 没有添加，因此需要添加。
    
    // 3.创建基本块（这个基本块是空的无内容）
    BasicBlock *entry = BasicBlock::Create(Context,"entrypoint",mainfunc);
    
    //4.设置插入点：插入点设置成相应BasicBlock，后面用builder创建的指令都会追加到这个BasicBlock里了
    //!!!: - 理解：上面的方式是通过直接往BasicBlock中添加Instruction方式来构建基本的BasicBlock，这里借助IRBuilder方式，往BasicBlock中添加命令
    builder.SetInsertPoint(entry);
    
    //5.添加全局字符串（IR中字符串全部为全局变量，使用数据序列来表示，每个元素是一个char类型）
    Value *hellocWord = builder.CreateGlobalString("hello world\n");
    //6.创建put函数
    //1)指定函数参数类型，装在一个数组中
    std::vector<Type*> putsargs;
    putsargs.push_back(builder.getInt8Ty()->getPointerTo());
    ArrayRef<Type*> argsRef(putsargs);
    //2)指定函数返回值类型
    FunctionType *putsType = FunctionType::get(builder.getInt32Ty(), argsRef, false);
    //3)创建“函数调用”，而不是创建函数
    FunctionCallee putsFunc = mod->getOrInsertFunction("puts",putsType);
    
    //7.调用函数 理解：通过createXXX创建出来的所有指令都在SetInsertPoint
    builder.CreateCall(putsFunc, hellocWord);
    
    //8.创建返回ret指令
    ConstantInt *zero = ConstantInt::get(IntegerType::getInt32Ty(Context), 0);
    builder.CreateRet(zero);
    
    //9.验证。
    llvm::VerifierAnalysis::Result Res;
    Res.IRBroken = llvm::verifyModule(*mod,&dbgs(),&Res.DebugInfoBroken);
    
    mod->dump();
    return mod;
}

Module* createVC()
{
    LLVMContext Context;
    Module *mod = new Module("vc.ll",Context);
    return mod;
}

