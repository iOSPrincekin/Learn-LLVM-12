//
//  factorial.hpp
//  CodeGen
//
//  Created by LEE on 7/18/22.
//

#ifndef factorial_hpp
#define factorial_hpp

#include <stdio.h>
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

class factorial{
private:
    Type *VoidTy;
    Type *Int8Ty;
    Type *Int32Ty;
    Type *Int64Ty;
    PointerType *VoidPtrTy;
    PointerType *Int8PtrTy;
    PointerType *Int32PtrTy;
    PointerType *Int8PtrPtrTy;
    Constant *Int8Zero;
    Constant *Int32Zero;
    Constant *Int64Zero;
    
    LLVMContext* Context;
    Module* M;
public:
    factorial();
    
    void generateIR();
    
};
#endif /* factorial_hpp */
