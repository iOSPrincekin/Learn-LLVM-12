BIN_DIR=/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin/
LLVM_DIR=/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/
LLC_CMD=${BIN_DIR}/llc
TBLGEN_CMD=${BIN_DIR}/llvm-tblgen
#${LLC_CMD} -mtriple=mips-linux-gnu \
#-stop-before=mips-delay-slot-filler -simplify-mir \
#< sum.ll  >delay.mir

#${TBLGEN_CMD} \
#-I${LLVM_DIR}/llvm/lib/Target/Mips/ \
#-I${LLVM_DIR}/llvm/include \
#${LLVM_DIR}/llvm/lib/Target/Mips/Mips.td

#${LLC_CMD} -mtriple=mips-linux-gnu -debug-only=isel < sum.ll

#${LLC_CMD} -view-dag-combine1-dags sum.ll > 1.txt

#${LLC_CMD} -fast-isel sum.ll

${LLC_CMD} -global-isel sum.ll
