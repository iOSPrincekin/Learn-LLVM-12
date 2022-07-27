	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.globl	__t3Gcd3GCD
	.p2align	4, 0x90
__t3Gcd3GCD:
	testq	%rsi, %rsi
	je	LBB0_4
	movq	%rsi, %rdx
	.p2align	4, 0x90
LBB0_2:
	movq	%rdi, %rax
	movq	%rdx, %rdi
	cqto
	idivq	%rdi
	testq	%rdx, %rdx
	jne	LBB0_2
	movq	%rdi, __t3Gcd1p(%rip)
LBB0_4:
	movq	%rdi, %rax
	retq

	.globl	__t3Gcd1x
.zerofill __DATA,__common,__t3Gcd1x,8,3
	.globl	__t3Gcd1p
.zerofill __DATA,__common,__t3Gcd1p,16,3
.subsections_via_symbols
