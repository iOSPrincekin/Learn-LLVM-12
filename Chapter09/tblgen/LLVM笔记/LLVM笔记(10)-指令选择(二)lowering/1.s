	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p0_m2p0_a2p0_c2p0"
	.file	"1.c"
	.globl	main
	.p2align	1
	.type	main,@function
main:
	addi	a0, zero, 6
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main

	.ident	"clang version 12.0.0 (git@github.com:iOSPrincekin/llvm-project.git 66ff30ec435a22065855c9edf1dcbf30cf647538)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
