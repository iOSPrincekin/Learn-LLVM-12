//
//  hello_world.hpp
//  CodeGen
//
//  Created by LEE on 7/14/22.
//

#ifndef hello_world_hpp
#define hello_world_hpp

#include <stdio.h>
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

class hello_world{
private:
    Type *VoidTy;
    Type *Int8Ty;
    Type *Int32Ty;
    Type *Int64Ty;
    PointerType *VoidPtrTy;
    PointerType *Int8PtrTy;
    PointerType *Int32PtrTy;
    PointerType *Int8PtrPtrTy;
    Constant *Int32Zero;
    Constant *Int64Zero;
    
    LLVMContext* Context;
    Module* M;
public:
    hello_world();
    void generateIR();
    Value * ConstString(const std::string &str_val,
                const std::string &name) const;
};
#endif /* hello_world_hpp */
