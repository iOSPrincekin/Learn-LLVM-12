//
//  main.cpp
//  CodeGen
//
//  Created by LEE on 7/12/22.
//
#include "hello_world.hpp"
#include "factorial.hpp"
#include "gep.hpp"
int main()
{
#if 0
    hello_world h;
    h.generateIR();
#elif 0
    factorial f;
    f.generateIR();
#else
    gen g;
    g.generateIR();
#endif
    return 0;
}
