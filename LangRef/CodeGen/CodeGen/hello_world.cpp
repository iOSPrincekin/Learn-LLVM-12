//
//  hello_world.cpp
//  CodeGen
//
//  Created by LEE on 7/14/22.
//

#include "hello_world.hpp"
hello_world::hello_world()
{
    LLVMContext *Context = new LLVMContext();
    M = new Module("hello_world.ll",*Context);
    VoidTy = Type::getVoidTy(M->getContext());
    Int8Ty = Type::getInt8Ty(M->getContext());
    Int32Ty = Type::getInt32Ty(M->getContext());
    Int64Ty = Type::getInt64Ty(M->getContext());
    Int8PtrTy = PointerType::get(Int8Ty,0);
    Int32PtrTy = Type::getInt32PtrTy(M->getContext());
    Int64PtrTy = Type::getInt64PtrTy(M->getContext());

    Int8PtrPtrTy = Int8PtrTy->getPointerTo();
    Int32Zero = ConstantInt::get(Int32Ty, 0,true);
    Int64Zero = ConstantInt::get(Int64Ty, 0,true);
}

void hello_world::generateIR()
{

    Constant* StrConstant = ConstantDataArray::getString(M->getContext(), "hello world\n");
    GlobalVariable *hello_world_GV = new GlobalVariable(*M,StrConstant->getType(),true,GlobalValue::PrivateLinkage,
                                                        StrConstant,".Str",nullptr,GlobalVariable::NotThreadLocal,0);
    hello_world_GV->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    
    FunctionType *Fty = FunctionType::get(Int32Ty, Int8PtrTy, false);
    Twine N = "puts";
    Function *Fn = Function::Create(Fty, GlobalVariable::ExternalLinkage, N,M);
    Fn->addFnAttr(Attribute::NoUnwind);

    //2、创建main函数
    FunctionType *ft = FunctionType::get(Int32Ty, std::vector<Type *>(), false);
    Function *mainFunc = Function::Create(ft, Function::ExternalLinkage, "main", M);
    // 创建最外层函数的basic
    BasicBlock *mainEntryBlock = BasicBlock::Create(M->getContext(),"entry",mainFunc,0);
    
    Value* cast210 =  ConstantInt::get(Int64Ty, 0);

    
    // We need an array of index values
    //   Note - we need a type for constants, so use someValue's type
    Value* indexList[2] = {ConstantInt::get(Int64Zero->getType(), 0), Int64Zero};
    Type *StrConstantType = StrConstant->getType();
    
    GetElementPtrInst* gepInst = GetElementPtrInst::Create(StrConstantType,hello_world_GV, ArrayRef<Value*>(indexList, 2), "cast210");
    mainEntryBlock->getInstList().insert(mainEntryBlock->getInstList().end(), gepInst);

    
    //2)指定函数返回值类型
    //3)创建“函数调用”，而不是创建函数
    // prototype free as "void free(void*)"
    FunctionCallee FreeFunc = M->getOrInsertFunction("puts", Fty);
    ArrayRef<Value *> args = gepInst;
    CallInst* Result = CallInst::Create(Fty, Fn,args,"call_puts",mainEntryBlock);
    
    ReturnInst *returnZero = ReturnInst::Create(mainFunc->getContext(),Int32Zero,mainEntryBlock);
    
    M->dump();
}
