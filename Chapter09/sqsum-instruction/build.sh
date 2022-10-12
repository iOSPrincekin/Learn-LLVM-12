BIN_DIR=/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin/
LLVM_DIR=/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/
LLVM_MC_CMD=${BIN_DIR}/llvm-mc
LLVM_LIT_CMD=${BIN_DIR}/llvm-lit
LLVM_LLC_CMD=${BIN_DIR}/llc
SQSUM_LL_FILE=${LLVM_DIR}/llvm/test/CodeGen/Mips/sqsum.ll
SQSUMU_S_FILE=${LLVM_DIR}/llvm/test/MC/Mips/sqsumu.s
#echo "sqsumu \$1,\$2,\$3" | ${LLVM_MC_CMD} --triple=mips64-linux-gnu -mattr=+sqsum --show-encoding

echo "${LLVM_LLC_CMD} –mtriple=mips64-linux-gnu –mattr=+sqsum < ${SQSUM_LL_FILE}"

${LLVM_LLC_CMD} –mtriple=mips64-linux-gnu –mattr=+sqsum  ${SQSUM_LL_FILE}
${LLVM_LIT_CMD} ${SQSUM_LL_FILE}

#${LLVM_LIT_CMD} ${SQSUMU_S_FILE}
