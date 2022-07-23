//
//  gep.cpp
//  CodeGen
//
//  Created by LEE on 7/18/22.
//

#include "gep.hpp"

gen::gen()
{
    LLVMContext *Context = new LLVMContext();
    M = new Module("gen.ll",*Context);
    VoidTy = Type::getVoidTy(M->getContext());
    Int8Ty = Type::getInt8Ty(M->getContext());
    Int32Ty = Type::getInt32Ty(M->getContext());
    Int64Ty = Type::getInt64Ty(M->getContext());
    Int8PtrTy = PointerType::get(Int8Ty,0);
    Int32PtrTy = Type::getInt32PtrTy(M->getContext());
    Int64PtrTy = Type::getInt64PtrTy(M->getContext());

    Int8PtrPtrTy = Int8PtrTy->getPointerTo();
    Int8Zero = ConstantInt::get(Int8Ty, 0,true);
    Int32Zero = ConstantInt::get(Int32Ty, 0,true);
    Int64Zero = ConstantInt::get(Int64Ty, 0,true);
}

void gen::generateIR(){
    Constant *helloString = ConstantDataArray::getString(M->getContext(), "hello\n");
    GlobalVariable *helloString_GV = new GlobalVariable(*M,helloString->getType(),true,GlobalValue::PrivateLinkage,helloString,"helloString",nullptr,GlobalVariable::NotThreadLocal,0);
    
    Constant *formatString = ConstantDataArray::getString(M->getContext(), "c:%d\n");
    GlobalVariable *formatString_GV = new GlobalVariable(*M,formatString->getType(),true,GlobalValue::PrivateLinkage,formatString,"formatString",nullptr,GlobalVariable::NotThreadLocal,0);
    
    // array1
    ArrayType* array1Type = ArrayType::get(IntegerType::get(M->getContext(), 8), 6);
    GlobalVariable* gArray1 = new GlobalVariable(/*Module=*/*M, 
    /*Type=*/array1Type,
    /*isConstant=*/false,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Initializer=*/0, // has initializer, specified below
    /*Name=*/"array1");
    //gvar_array_a->setAlignment(16);

    // Constant Definitions
    ConstantAggregateZero* constArray1Type = ConstantAggregateZero::get(array1Type);

    // Global Variable Definitions
    gArray1->setInitializer(constArray1Type);
    
    
    // MyStruct1
    std::vector<Type*> MyStruct1TypeMembers;
    MyStruct1TypeMembers.push_back( IntegerType::get(  M->getContext(), 8 ) );
    MyStruct1TypeMembers.push_back( IntegerType::get(  M->getContext(), 32 ) );
    ArrayType*MyStruct1ArrayType = ArrayType::get( IntegerType::get( M->getContext(), 32 ), 3);
    MyStruct1TypeMembers.push_back(MyStruct1ArrayType);
    StructType * MyStruct1Type = StructType::create(M->getContext(), "MyStruct1");
    MyStruct1Type->setBody( MyStruct1TypeMembers );
    
    GlobalVariable *MyStruct1 = new GlobalVariable(*M, MyStruct1Type, false,
                                 GlobalValue::ExternalLinkage, nullptr,"struct1");
    
    Constant* int8_v99 = ConstantInt::get(Int8Ty, 99,false);
    Constant* int32_v17 = ConstantInt::get(Int32Ty, 17,false);
    ArrayRef MyStruct1Array = {1,2,3};
    Constant* MyStruct1ArrayConstant = ConstantDataArray::get(M->getContext(), MyStruct1Array);

    ArrayRef<Constant*> MyStruct1ConstantArray = {int8_v99,int32_v17,MyStruct1ArrayConstant};


    Constant* ConstMyStruct1 = ConstantStruct::get(MyStruct1Type, MyStruct1ConstantArray);
    MyStruct1->setInitializer(ConstMyStruct1);
    
    // array2
    ArrayType* array2Type = ArrayType::get(Int8Ty, 4);
    GlobalVariable* gArray2 = new GlobalVariable(/*Module=*/*M, 
    /*Type=*/array2Type,
    /*isConstant=*/false,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Initializer=*/0, // has initializer, specified below
    /*Name=*/"array2");
    //gvar_array_a->setAlignment(16);

    // Constant Definitions
    Constant* int8_v0 = ConstantInt::get(Int8Ty, 0,false);
    Constant* int8_v1 = ConstantInt::get(Int8Ty, 1,false);
    Constant* int8_v2 = ConstantInt::get(Int8Ty, 2,false);
    Constant* int8_v3 = ConstantInt::get(Int8Ty, 3,false);
    
    Constant* int32_v1 = ConstantInt::get(Int32Ty, 1,false);
    Constant* int32_v2 = ConstantInt::get(Int32Ty, 2,false);
#if 0

    SmallVector<Constant *, 4> arrayRef2Data = {int8_v0,int8_v1,int8_v2,int8_v3};
    Constant* constArray2Data = ConstantArray::get(array2Type, arrayRef2Data);

#else
    ArrayRef<uint8_t> arrayRef2Data = {0,1,2,3};
    Constant* constArray2Data = ConstantDataArray::get(M->getContext(), arrayRef2Data);
#endif
    // Global Variable Definitions
    gArray2->setInitializer(constArray2Data);
    
    // array3
    ArrayType* array3Type = ArrayType::get(Int8Ty, 4);
    GlobalVariable* gArray3 = new GlobalVariable(/*Module=*/*M, 
    /*Type=*/array3Type,
    /*isConstant=*/false,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Initializer=*/0, // has initializer, specified below
    /*Name=*/"array3");
    //gvar_array_a->setAlignment(16);


    ArrayRef<uint8_t> arrayRef3Data = {4,5,6,7};
    Constant* constArray3Data = ConstantDataArray::get(M->getContext(), arrayRef3Data);
    // Global Variable Definitions
    gArray3->setInitializer(constArray3Data);

    
    // MyStruct2
    std::vector<Type*> MyStruct2TypeMembers;
    PointerType* array2TypePtr = PointerType::get(array2Type, 0);
    printf("array2TypePtr->dump()---\n");
    array2TypePtr->dump();
    PointerType* array3TypePtr = PointerType::get(array3Type, 0);
    printf("array3TypePtr->dump()---\n");
    array3TypePtr->dump();
    
    MyStruct2TypeMembers.push_back( array2TypePtr );
    MyStruct2TypeMembers.push_back( array3TypePtr );
    StructType * MyStruct2Type = StructType::create(M->getContext(), "MyStruct2");
    MyStruct2Type->setBody( MyStruct2TypeMembers );
    
    GlobalVariable *MyStruct2 = new GlobalVariable(*M, MyStruct2Type, false,
                                 GlobalValue::ExternalLinkage, nullptr,"struct2");
    

    Constant *constArray2DataX = ConstantExpr::getBitCast(gArray2, array2TypePtr);
    constArray2DataX->dump();
    Constant *constArray3DataX = ConstantExpr::getBitCast(gArray3, array3TypePtr);
    constArray2DataX->dump();
    ArrayRef<Constant*> MyStruct2ConstantArray = {constArray2DataX,constArray3DataX};


    Constant* ConstMyStruct2 = ConstantStruct::get(MyStruct2Type, MyStruct2ConstantArray);
    MyStruct2->setInitializer(ConstMyStruct2);
    M->dump();
    // 创建 main 函数
    FunctionType *mainFT = FunctionType::get(Int32Ty, std::vector<Type*>(), false);
    Function *mainFN = Function::Create(mainFT, Function::ExternalLinkage, "main",M);
    // 创建最外层函数的basic
    BasicBlock *mainEntryBlock = BasicBlock::Create(M->getContext(),"entry",mainFN,0);
    
    // printf helloString
    Type* printfArgTys[] = {Int8PtrTy};
    FunctionType *printfFT = FunctionType::get(Int32Ty, printfArgTys, true);
    Function *printFN = Function::Create(printfFT, Function::ExternalLinkage, "printf",M);
    
    Type* helloStringType = helloString->getType();
    Value* helloStringIndex[2] = {Int32Zero,Int32Zero};
    GetElementPtrInst* helloStringInst = GetElementPtrInst::CreateInBounds(helloStringType,helloString_GV,ArrayRef<Value*>(helloStringIndex,2),"helloStringPtr",mainEntryBlock);
    ArrayRef<Value *> printfArgs = {helloStringInst};
    CallInst* printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call1",mainEntryBlock);
    
    Value* array1Index = {Int32Zero};
    // [6*i8] array
    GetElementPtrInst*array1_new_ptr = GetElementPtrInst::Create(array1Type, gArray1, array1Index,"array1_new_ptr",mainEntryBlock);
    Value* array1_elem_Index[2] = {Int32Zero,Int32Zero};
    GetElementPtrInst*array1_elem_ptr = GetElementPtrInst::Create(array1Type, gArray1, array1_elem_Index,"array1_elem_ptr",mainEntryBlock);
    
    //8.使用load命令
    LoadInst *array1_elem_val_Inst = new LoadInst(/*类型*/Int8Ty,array1_elem_ptr,/*名称*/"array1_elem_val",mainEntryBlock);
    StoreInst *st0 = new StoreInst(int8_v2,array1_elem_ptr,/* 指定是否是静态存储区 */false,mainEntryBlock);

    Type* formatStringType = formatString->getType();
    Value* formatStringIndex[2] = {Int32Zero,Int32Zero};
    GetElementPtrInst* formatStringInst = GetElementPtrInst::CreateInBounds(formatStringType, formatString_GV,ArrayRef<Value*>(formatStringIndex,2),"formatStringPtr",mainEntryBlock);
    printfArgs = {formatStringInst,array1_elem_val_Inst};
    
    printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call2",mainEntryBlock);
    
    
    LoadInst *array1_elem_val1_Inst = new LoadInst(/*类型*/Int8Ty,array1_elem_ptr,/*名称*/"array1_elem_val1",mainEntryBlock);
    printfArgs = {formatStringInst,array1_elem_val1_Inst};
    printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call3",mainEntryBlock);
    
    //%MyStruct1 = type < { i8, i32, [3 x i32] }>
    Value* MyStruct1Index[1] = {Int32Zero};
    GetElementPtrInst *struct1_new_ptr1_Inst = GetElementPtrInst::CreateInBounds(MyStruct1Type, MyStruct1, MyStruct1Index, "struct1_new_ptr1", mainEntryBlock);
    
    Value* MyStruct2Index[2] = {Int32Zero,Int32Zero};
    GetElementPtrInst *struct1_new_ptr2_Inst = GetElementPtrInst::CreateInBounds(MyStruct1Type, MyStruct1, MyStruct2Index, "struct1_new_ptr2", mainEntryBlock);
    
    Value* MyStruct3Index[3] = {Int32Zero,int32_v2,Int32Zero};
    GetElementPtrInst *struct1_new_ptr3_Inst = GetElementPtrInst::CreateInBounds(MyStruct1Type, MyStruct1, MyStruct3Index, "struct1_new_ptr3", mainEntryBlock);
    
    LoadInst* struct1_elem_val2_Inst = new LoadInst(Int8Ty,struct1_new_ptr2_Inst,"struct1_elem_val2",mainEntryBlock);
    LoadInst* struct1_elem_val3_Inst = new LoadInst(Int32Ty,struct1_new_ptr3_Inst,"struct1_elem_val3",mainEntryBlock);
    
    printfArgs = {formatStringInst,struct1_elem_val2_Inst};
    printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call5",mainEntryBlock);
    
    printfArgs = {formatStringInst,struct1_elem_val3_Inst};
    printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call6",mainEntryBlock);
    
    Value* struct2_new_ptr1_Index[2] = {Int32Zero,int32_v1};
    GetElementPtrInst* struct2_new_ptr1_Inst = GetElementPtrInst::Create(MyStruct2Type, MyStruct2, struct2_new_ptr1_Index,"struct2_new_ptr1", mainEntryBlock);

    struct2_new_ptr1_Inst->dump();
    array2Type->dump();
    PointerType*array2TypePoint = PointerType::get(array2Type, 8);
    array2TypePoint->dump();
    
    LoadInst* strcut2_loaded_ptr_Inst = new LoadInst(array2TypePtr, struct2_new_ptr1_Inst, "strcut2_loaded_ptr", mainEntryBlock);
    ArrayRef<Value *> goal1Index = {Int32Zero,int32_v1};
    GetElementPtrInst *goal1Inst = GetElementPtrInst::Create(array2Type, strcut2_loaded_ptr_Inst, goal1Index,"goal1", mainEntryBlock);
    LoadInst *goal2Inst = new LoadInst(Int8Ty, goal1Inst, "goal2", mainEntryBlock);
    printfArgs = {formatStringInst,goal2Inst};
    printfResult = CallInst::Create(printfFT, printFN,printfArgs,"call7",mainEntryBlock);
    
    ReturnInst* retInst = ReturnInst::Create(M->getContext(), Int32Zero, mainEntryBlock);
    M->dump();
}
