//
//  factorial.cpp
//  CodeGen
//
//  Created by LEE on 7/18/22.
//

#include "factorial.hpp"

factorial::factorial()
{
    LLVMContext *Context = new LLVMContext();
    M = new Module("factorial.ll",*Context);
    VoidTy = Type::getVoidTy(M->getContext());
    Int8Ty = Type::getInt8Ty(M->getContext());
    Int32Ty = Type::getInt32Ty(M->getContext());
    Int64Ty = Type::getInt64Ty(M->getContext());
    Int8PtrTy = PointerType::get(Int8Ty,0);
    Int32PtrTy = Type::getInt32PtrTy(M->getContext());
    Int8PtrPtrTy = Int8PtrTy->getPointerTo();
    Int8Zero = ConstantInt::get(Int8Ty, 0,true);
    Int32Zero = ConstantInt::get(Int32Ty, 0,true);
    Int64Zero = ConstantInt::get(Int64Ty, 0,true);
}

void factorial::generateIR()
{
    
    Constant* formatString = ConstantDataArray::getString(M->getContext(), "c:%d\00");
    GlobalVariable *formatString_GV = new GlobalVariable(*M,formatString->getType(),true,GlobalValue::PrivateLinkage,
                                                         formatString,"formatString",nullptr,GlobalVariable::NotThreadLocal,0);
    
    // 创建 factorial1 函数
    FunctionType *factorial1FT = FunctionType::get(Int32Ty, Int32Ty, false);
    Twine N = "factorial1";
    Function *factorial1FN = Function::Create(factorial1FT, GlobalVariable::ExternalLinkage, N,M);
    factorial1FN->addFnAttr(Attribute::NoUnwind);
    for(auto arg = factorial1FN->arg_begin(); arg != factorial1FN->arg_end(); ++arg) {
        if(auto* ci = dyn_cast<ConstantInt>(arg))
            errs() << ci->getValue() << "\n";
        errs() << *arg << "\n";
    }
    Argument* factorial1FNArg1 = factorial1FN->arg_begin();
    // 创建最外层函数的basic
    BasicBlock *factorial1EntryBlock = BasicBlock::Create(M->getContext(),"entry",factorial1FN,0);
    CmpInst *is_base_case_cmp_Inst = CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_EQ,Int32Zero, factorial1FNArg1,"is_base_case",factorial1EntryBlock);

    // 创建br用的basicblock
    BasicBlock *base_case = BasicBlock::Create(M->getContext(),"base_case",factorial1FN,NULL);
    Constant* int32_v1= ConstantInt::get(Int32Ty, 1,false);
    ReturnInst *factorialReturn_v1 = ReturnInst::Create(factorial1FN->getContext(),int32_v1,base_case);
    
    
    
    BasicBlock *recursive_case = BasicBlock::Create(M->getContext(),"recursive_case",factorial1FN,NULL);
    Constant* int32_v_1 = ConstantInt::get(Int32Ty, -1,false);

    Instruction *add1 = BinaryOperator::Create(Instruction::Add, factorial1FNArg1, int32_v_1,"",recursive_case);
    ArrayRef<Value *> factorial1Args = {add1};
    CallInst *factorial1CallInst = CallInst::Create(factorial1FT, factorial1FN,factorial1Args,"", recursive_case);
    Instruction *mul1 = BinaryOperator::Create(Instruction::Mul, factorial1CallInst, factorial1FNArg1,"",recursive_case);
    ReturnInst *recursive_case_ReturnInst = ReturnInst::Create(M->getContext(), mul1, recursive_case);
    
    // br
    BranchInst::Create(base_case,recursive_case,is_base_case_cmp_Inst,factorial1EntryBlock);
    
    // 创建 factorial2 函数
    FunctionType *factorial2FT = FunctionType::get(Int32Ty, Int32Ty, false);
    Function *factorial2FN = Function::Create(factorial2FT, GlobalVariable::ExternalLinkage, "factorial2",M);
    factorial2FN->addFnAttr(Attribute::NoUnwind);
    for(auto arg = factorial2FN->arg_begin(); arg != factorial2FN->arg_end(); ++arg) {
        if(auto* ci = dyn_cast<ConstantInt>(arg))
            errs() << ci->getValue() << "\n";
        errs() << *arg << "\n";
    }
    Argument* factorial2FNArg1 = factorial2FN->arg_begin();
    // 创建最外层函数的basic
    BasicBlock *factorial2EntryBlock = BasicBlock::Create(M->getContext(),"entry",factorial2FN,0);

    BasicBlock *factorial2_for_body = NULL;
    BinaryOperator *factorial2_new_temp = NULL;
    // label: check_for_condition
    BasicBlock *factorial2_check_for_condition = BasicBlock::Create(M->getContext(),"check_for_condition",factorial2FN,NULL);

  //  AllocaInst *tempAllocaInst = new AllocaInst(/*要创建的内存空间类型*/Int32Ty,/*地址空间*/M->getDataLayout().getAllocaAddrSpace(),/*名称*/"temp",factorial2_check_for_condition);
    
    PHINode *factorial2_current_i = PHINode::Create(Int32Ty, 0, "current_i", factorial2_check_for_condition);
    Constant*Int32_v2 = ConstantInt::get(Int32Ty, 2);
    factorial2_current_i->addIncoming(Int32_v2, factorial2EntryBlock);
    PHINode *factorial2_temp = PHINode::Create(Int32Ty, 0, "temp", factorial2_check_for_condition);
    Constant*Int32_v1 = ConstantInt::get(Int32Ty, 1);
    factorial2_temp->addIncoming(Int32_v1, factorial2EntryBlock);
    CmpInst *factorial2_i_leq_val = CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_SLE,factorial2_current_i, factorial2FNArg1,"i_leq_val",factorial2_check_for_condition);

    
    // br
    BranchInst::Create(factorial2_check_for_condition,factorial2EntryBlock);
    

    // label: for_body
    factorial2_for_body = BasicBlock::Create(M->getContext(),"for_body",factorial2FN,NULL);
    factorial2_new_temp = BinaryOperator::Create(Instruction::Mul, factorial2_temp, factorial2_current_i,"new_temp",factorial2_for_body);
    factorial2_temp->addIncoming(factorial2_new_temp, factorial2_for_body);
    BinaryOperator *factorial2_i_plus_one = BinaryOperator::Create(Instruction::Add, factorial2_current_i, Int32_v1,"i_plus_one",factorial2_for_body);
    factorial2_current_i->addIncoming(factorial2_i_plus_one, factorial2_for_body);
    BranchInst::Create(factorial2_check_for_condition,factorial2_for_body);
    
    // label: end_loop
    BasicBlock*factorial2_end_loop = BasicBlock::Create(M->getContext(),"end_loop",factorial2FN,NULL);
    ReturnInst *factorial2_returnInst = ReturnInst::Create(M->getContext(), factorial2_temp, factorial2_end_loop);
    
    BranchInst::Create(factorial2_for_body,factorial2_end_loop,factorial2_i_leq_val,factorial2_check_for_condition);

    // 创建 factorial2 函数
    FunctionType *factorial3FT = FunctionType::get(Int32Ty, Int32Ty, false);
    Function *factorial3FN = Function::Create(factorial3FT, GlobalVariable::ExternalLinkage, "factorial3",M);
    factorial3FN->addFnAttr(Attribute::NoUnwind);
    BasicBlock *factorial3EntryBlock = BasicBlock::Create(M->getContext(),"entry",factorial3FN,0);
    
    AllocaInst *factorial3_i_addr = new AllocaInst(/*要创建的内存空间类型*/Int32Ty,/*地址空间*/M->getDataLayout().getAllocaAddrSpace(),/*名称*/"i.addr",/*BasicBlock*/factorial3EntryBlock);
    AllocaInst *factorial3_temp_addr1 = new AllocaInst(Int32Ty,M->getDataLayout().getAllocaAddrSpace(),"temp.addr1",factorial3EntryBlock);
    //7.使用store指令
    StoreInst *factorial3_i_addr_st = new StoreInst(Int32_v2,factorial3_i_addr,/* 指定是否是静态存储区 */false,factorial3EntryBlock);
    StoreInst *factorial3_temp_addr1_st = new StoreInst(Int32_v1,factorial3_temp_addr1,/* 指定是否为静态存储区*/false,factorial3EntryBlock);
    BasicBlock *factorial3_check_for_condition = BasicBlock::Create(M->getContext(),"check_for_condition",factorial3FN,NULL);
    
    LoadInst *factorial3_current_i = new LoadInst(Int32Ty, factorial3_i_addr, "current_i", factorial3_check_for_condition);
    LoadInst *factorial3_temp = new LoadInst(
                                             Int32Ty,factorial3_temp_addr1,"temp",factorial3_check_for_condition);
    Argument* factorial3FNArg1 = factorial3FN->arg_begin();
    CmpInst *factorial3_i_leq_val = CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_SLE,factorial3_current_i, factorial3FNArg1,"i_leq_val",factorial3_check_for_condition);
    
    
    // label: for_body
    BasicBlock*factorial3_for_body = BasicBlock::Create(M->getContext(),"for_body",factorial3FN,NULL);
    BinaryOperator *factorial3_i_plus_one = BinaryOperator::Create(Instruction::Add, factorial3_current_i, Int32_v1,"i_plus_one",factorial3_for_body);
    BinaryOperator *factorial3_new_temp = BinaryOperator::Create(Instruction::Mul, factorial3_temp, factorial3_current_i,"new_temp",factorial3_for_body);

    factorial3_i_addr_st = new StoreInst(factorial3_i_plus_one,factorial3_i_addr,/* 指定是否是静态存储区 */false,factorial3_for_body);
    factorial3_temp_addr1_st = new StoreInst(factorial3_new_temp,factorial3_temp_addr1,/* 指定是否为静态存储区*/false,factorial3_for_body);
    
    BranchInst::Create(factorial3_check_for_condition,factorial3_for_body);
    
    // label: end_loop
    BasicBlock*factorial3_end_loop = BasicBlock::Create(M->getContext(),"end_loop",factorial3FN,NULL);
    ReturnInst *factorial3_returnInst = ReturnInst::Create(M->getContext(), factorial3_temp, factorial3_end_loop);
    
    BranchInst::Create(factorial3_for_body,factorial3_end_loop,factorial3_i_leq_val,factorial3_check_for_condition);

    
    BranchInst::Create(factorial3_check_for_condition,factorial3EntryBlock);
    
    
    
    
    //2、创建main函数
    FunctionType *mainFT = FunctionType::get(Int32Ty, std::vector<Type *>(), false);
    Function *mainFN = Function::Create(mainFT, Function::ExternalLinkage, "main", M);
    // 创建最外层函数的basic
    BasicBlock *mainEntryBlock = BasicBlock::Create(M->getContext(),"entry",mainFN,0);
    
    //2)指定函数返回值类型
    //3)创建“函数调用”，而不是创建函数
    // prototype free as "void free(void*)"
    Constant* int32_v4 = ConstantInt::get(Int32Ty, 4,false);
    ArrayRef<Value *> factorialArgs = int32_v4;
    CallInst* factorialResult = CallInst::Create(factorial1FT, factorial1FN,factorialArgs,"",mainEntryBlock);
    // We need an array of index values
    //   Note - we need a type for constants, so use someValue's type
    Value* indexList[2] = {Int32Zero, Int32Zero};
    Type *formatStringType = formatString->getType();
    
    GetElementPtrInst* gepInst = GetElementPtrInst::CreateInBounds(formatStringType,formatString_GV, ArrayRef<Value*>(indexList, 2), "formatStringPtr");
    
    mainEntryBlock->getInstList().insert(mainEntryBlock->getInstList().end(), gepInst);
    
    Type *printfArgTys[] = {Int8PtrTy,Int32Ty};
    FunctionType *printfFT = FunctionType::get(Int32Ty, printfArgTys, false);
    Function *printfFN = Function::Create(printfFT, Function::ExternalLinkage, "printf",M);
    

    ArrayRef<Value *> printfArgs = {gepInst,factorialResult};
    
    CallInst* printfResult = CallInst::Create(printfFT, printfFN,printfArgs,"call",mainEntryBlock);

    Instruction *mul2 = BinaryOperator::Create(Instruction::Mul, factorialResult, ConstantInt::get(Int32Ty, 7),"",mainEntryBlock);
    
    Constant* int32_v42 = ConstantInt::get(Int32Ty, 42,false);

    CmpInst *cmp1 = CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_EQ,mul2, int32_v42,"",mainEntryBlock);
    
    CastInst *z = ZExtInst::CreateIntegerCast(cmp1, Int32Ty, false,"result",mainEntryBlock);
        
    ReturnInst *mainReturnZero = ReturnInst::Create(mainFN->getContext(),z,mainEntryBlock);
    
    M->dump();
}
