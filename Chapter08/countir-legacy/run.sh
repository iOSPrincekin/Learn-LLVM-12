OPT=/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin/opt
PASS_DYLIB=/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter08/countir/build-countir/lib/Debug/CountIR.dylib
DEMO_LL=/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter08/demo.ll
${OPT} --passes="countir" --disable-output --stats ${DEMO_LL}

