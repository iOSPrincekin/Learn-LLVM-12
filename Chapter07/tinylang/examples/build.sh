#!/bin/bash
TARGET=Gcd
PROGRAM=prog
rm -rf ${PROGRAM} ${PROGRAM}.o
cat ${TARGET}.ll |  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/bin/llc -filetype obj -o ${PROGRAM}.o
clang -o ${PROGRAM} ${PROGRAM}.o
${PROGRAM}
