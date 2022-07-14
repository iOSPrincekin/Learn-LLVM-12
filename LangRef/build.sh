#!/bin/bash
TARGET=gep
PROGRAM=prog
rm -rf ${PROGRAM} ${PROGRAM}.o
cat ${TARGET}.ll |  llc -filetype obj -o ${PROGRAM}.o
clang -o ${PROGRAM} ${PROGRAM}.o
${PROGRAM}
