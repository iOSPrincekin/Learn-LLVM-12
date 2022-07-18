//
//  main.cpp
//  CodeGen
//
//  Created by LEE on 7/12/22.
//
#include "hello_world.hpp"
#include "factorial.hpp"
int main()
{
#if 0
    hello_world h;
    h.generateIR();
#else
    factorial f;
    f.generateIR();
#endif
    return 0;
}
