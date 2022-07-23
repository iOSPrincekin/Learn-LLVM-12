//
//  main.cpp
//  CodeGen
//
//  Created by LEE on 7/12/22.
//
#include "hello_world.hpp"
#include "factorial.hpp"
#include "gep.hpp"
#include "CodeGen.hpp"

int main()
{
#if 0
    CodeGen codeGen;
    codeGen.createLLVMWhileModule();
#elif 0
    hello_world h;
    h.generateIR();
#elif 1
    factorial f;
    f.generateIR();
#else
    gen g;
    g.generateIR();
#endif
    return 0;
}
