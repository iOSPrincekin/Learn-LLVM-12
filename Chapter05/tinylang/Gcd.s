	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.globl	__t3Gcd3GCD
	.p2align	4, 0x90
__t3Gcd3GCD:
	.cfi_startproc
	movq	%rdi, %rax
	.p2align	4, 0x90
LBB0_1:
	testq	%rsi, %rsi
	jne	LBB0_1
	retq
	.cfi_endproc

.subsections_via_symbols
