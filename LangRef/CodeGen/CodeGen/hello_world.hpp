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
public:
    static void generateIR();
};
#endif /* hello_world_hpp */
