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
    Int32Zero = ConstantInt::get(Int32Ty, 0,true);
    Int64Zero = ConstantInt::get(Int64Ty, 0,true);
}

void factorial::generateIR()
{
    
    Constant* formatString = ConstantDataArray::getString(M->getContext(), "c:%d\00");
    GlobalVariable *formatString_GV = new GlobalVariable(*M,formatString->getType(),true,GlobalValue::PrivateLinkage,
                                                         formatString,"formatString",nullptr,GlobalVariable::NotThreadLocal,0);
    
    FunctionType *factorialFT = FunctionType::get(Int32Ty, Int8Ty, false);
    Twine N = "factorial1";
    Function *factorialFN = Function::Create(factorialFT, GlobalVariable::ExternalLinkage, N,M);
    factorialFN->addFnAttr(Attribute::NoUnwind);
    
    // 创建最外层函数的basic
    BasicBlock *factorialEntryBlock = BasicBlock::Create(M->getContext(),"entry",factorialFN,0);
    Constant* int32_v8 = ConstantInt::get(Int32Ty, 8,false);
    // 创建br用的basicblock
    ReturnInst *factorialReturnZero = ReturnInst::Create(factorialFN->getContext(),int32_v8,factorialEntryBlock);

    
    //2、创建main函数
    FunctionType *mainFT = FunctionType::get(Int32Ty, std::vector<Type *>(), false);
    Function *mainFN = Function::Create(mainFT, Function::ExternalLinkage, "main", M);
    // 创建最外层函数的basic
    BasicBlock *mainEntryBlock = BasicBlock::Create(M->getContext(),"entry",mainFN,0);
    
    //2)指定函数返回值类型
    //3)创建“函数调用”，而不是创建函数
    // prototype free as "void free(void*)"
    Constant* int8_v4 = ConstantInt::get(Int8Ty, 4,false);
    ArrayRef<Value *> factorialArgs = int8_v4;
    CallInst* factorialResult = CallInst::Create(factorialFT, factorialFN,factorialArgs,"",mainEntryBlock);
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

    Instruction *mul1 = BinaryOperator::Create(Instruction::Mul, factorialResult, ConstantInt::get(Int32Ty, 7),"",mainEntryBlock);
    
    Constant* int32_v42 = ConstantInt::get(Int32Ty, 42,false);

    CmpInst *cmp1 = CmpInst::Create(Instruction::ICmp, CmpInst::ICMP_EQ,mul1, int32_v42,"",mainEntryBlock);
    
    CastInst *z = ZExtInst::CreateIntegerCast(cmp1, Int32Ty, false,"result",mainEntryBlock);
        
    ReturnInst *mainReturnZero = ReturnInst::Create(mainFN->getContext(),z,mainEntryBlock);
    
    M->dump();
}
