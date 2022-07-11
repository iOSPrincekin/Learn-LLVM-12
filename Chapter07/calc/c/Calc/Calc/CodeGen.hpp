//
//  CodeGen.hpp
//  Calc
//
//  Created by LEE on 7/10/22.
//

#ifndef CodeGen_hpp
#define CodeGen_hpp

#include <stdio.h>
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;
class CodeGen{
public:
    void compile();
    Module *createLLVMSumModule();
    Module *createLLVMWhileModule();
    Module* createIRWithIRBuilder();
    
};

#endif /* CodeGen_hpp */
