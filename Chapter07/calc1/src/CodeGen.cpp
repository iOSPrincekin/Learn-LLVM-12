#include "CodeGen.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{
class ToIRVisitor : public ASTVisitor{
    Module *M;
    IRBuilder<> Builder;
    Type* VoidTy;
    Type* Int8Ty;
    Type* Int32Ty;
    Type* Int64Ty;
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
    StringMap<Value *>nameMap;
    
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
    Int32Zero = ConstantInt::get(Int32Ty, true);
    
    TypeInfo = nullptr;
    AllocEHFty = nullptr;
    AllocEHFn = nullptr;
    ThrowEHFty = nullptr;
    ThrowEHFn = nullptr;
    }
    
    void run(AST *Tree)
    {
    FunctionType *MainFty = FunctionType::get(Int32Ty,{Int32Ty,Int8PtrPtrTy},false);
    Function *MainFn = Function::Create(MainFty, GlobalVariable::ExternalLinkage, "main",M);
    BasicBlock *BB = BasicBlock::Create(M->getContext(),"entry",MainFn);
    Builder.SetInsertPoint(BB);
    
    Tree->accept(*this);
    
    FunctionType *CalaWriteFnTy = FunctionType::get(VoidTy, {Int32Ty}, false);
    Function *CalcWriteFn = Function::Create(CalaWriteFnTy, GlobalVariable::ExternalLinkage, "calc_write",M);
    Builder.CreateCall(CalaWriteFnTy, CalcWriteFn,{V});
    
    Builder.CreateRet(Int32Zero);
    }
    
    virtual void visit(Factor &Node) override {
        if (Node.getKind() == Factor::Ident) {
            V = nameMap[Node.getVal()];
        }else{
            int intVal;
            Node.getVal().getAsInteger(10, intVal);
            V = ConstantInt::get(Int32Ty, intVal,true);
        }
    }
    
    virtual void visit(BinaryOp &Node) override{
        Node.getLeft()->accept(*this);
        Value*Left = V;
        Node.getRight()->accept(*this);
        Value*Right = V;
        switch(Node.getOperator())
            {
                case BinaryOp::Plus:
                V = Builder.CreateNSWAdd(Left, Right);
                break;
                case BinaryOp::Minus:
                V = Builder.CreateNSWSub(Left, Right);
                break;
                case BinaryOp::Mul:
                V = Builder.CreateNSWMul(Left, Right);
                break;
                case BinaryOp::Div:
                BasicBlock *TrueDest, *FalseDest;
                
            }
    }
    
    
    void createICmpEq(Value *Left,Value *Right,BasicBlock *&TrueDest,BasicBlock *&FalseDest,const Twine &TrueLabel = "",const Twine &FalseLabel = "")
    {
    Function *Fn = Builder.GetInsertBlock()->getParent();
    TrueDest = BasicBlock::Create(M->getContext(),TrueLabel,Fn);
    FalseDest = BasicBlock::Create(M->getContext(),FalseLabel,Fn);
    Value *Cmp = Builder.CreateCmp(CmpInst::ICMP_EQ, Left, Right);
    Builder.CreateCondBr(Cmp, TrueDest, FalseDest);
    }
    
    void createFunc(FunctionType *&Fty,Function *&Fn,const Twine &N,Type *Result,ArrayRef<Type *> Params = None,bool isVarArgs = false)
    {
    Fty = FunctionType::get(Result, Params, isVarArgs);
    Fn = Function::Create(Fty, GlobalVariable::ExternalLinkage, N,M);
    }
    
    void addThrow(int PayloadVal)
    {
    if (!TypeInfo) {
        TypeInfo = new GlobalVariable(*M,Int8PtrTy,
                                      /*isConstant=*/true,GlobalVariable::ExternalLinkage,/*Initializer=*/nullptr,"_ZTIi");
        
        // Declare the __cxa_allocate_exception function
        createFunc(AllocEHFty, AllocEHFn, "__cxa_allocate_exception", Int8PtrTy,{Int64Ty});
        
        // Declare the __cxz_throw function
        createFunc(ThrowEHFty, ThrowEHFn, "__cxz_throw", VoidTy,{Int8PtrTy,Int8PtrTy,Int8PtrTy});
        
        // Declare personality function
        FunctionType *PersFty;
        Function *PersFn;
        createFunc(PersFty, PersFn,"__gxx_personality_v0" , Int32Ty,None,true);
        
        // Attach personality function to main()
        Function *Fn = Builder.GetInsertBlock()->getParent();
        Fn->setPersonalityFn(PersFn);
        
        // Create and populate the landingpad block and
        // the resume block.
        BasicBlock *SaveBB = Builder.GetInsertBlock();
        LPadBB = BasicBlock::Create(M->getContext(),"lpad",Fn);
        Builder.SetInsertPoint(LPadBB);
        
    }
    }
    
    void addLandingPad()
    {
    assert(TypeInfo && "TypeInfo should be not null");
    
    FunctionType *TypeIdFty;
    Function *TypeIdFn;
    createFunc(TypeIdFty, TypeIdFn, "llvm.eh.typeid.for", Int32Ty,{Int8PtrTy});
    
    FunctionType *EndCatchFty;
    Function *EndCatchFn;
    createFunc(EndCatchFty, EndCatchFn, "__cxa_end_catch", VoidTy);
    
    FunctionType *PutsFty;
    Function *PutsFn;
    createFunc(PutsFty, PutsFn, "puts", Int32Ty,{Int8PtrTy});
    
    LandingPadInst *Exc = Builder.CreateLandingPad(StructType::get(Int8PtrTy, Int32Ty), 1,"exec");
    Exc->addClause(ConstantExpr::getBitCast(TypeInfo, Int8PtrTy));
    Value *Sel = Builder.CreateExtractValue(Exc, {1},"exc.sel");
    CallInst *Id = Builder.CreateCall(
                                      TypeIdFty, TypeIdFn, {ConstantExpr::getBitCast(TypeInfo, Int8PtrTy)});
    
    BasicBlock *TrueDest, *FalseDest;
    createICmpEq(Sel, Id, TrueDest, FalseDest,"match","resume");
    Builder.SetInsertPoint(FalseDest);
    Builder.CreateResume(Exc);
    Builder.SetInsertPoint(TrueDest);
    Value *Ptr = Builder.CreateExtractValue(Exc, {0},"exc.ptr");
    Builder.CreateCall(BeginCatchFty, BeginCatchFn, {Ptr});
    
    
    
    }
};
}
