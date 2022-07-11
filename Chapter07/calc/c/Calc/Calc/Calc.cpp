#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "CodeGen.hpp"


using namespace llvm;

int main()
{
    CodeGen CodeGenerator;
 //   CodeGenerator.compile();
 //   CodeGenerator.createLLVMSumModule();
    CodeGenerator.createLLVMWhileModule();
    return 0;
}



