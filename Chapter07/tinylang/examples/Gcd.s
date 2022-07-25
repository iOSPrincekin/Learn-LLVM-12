	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.globl	__t3Gcd3GCD
	.p2align	4, 0x90
__t3Gcd3GCD:
	.cfi_startproc
	movq	%rdi, %rax
	testq	%rsi, %rsi
	jne	LBB0_1
	retq
	.p2align	4, 0x90
LBB0_2:
	cqto
	idivq	%rsi
	movq	%rsi, %rax
	movq	%rdx, %rsi
LBB0_1:
	testq	%rsi, %rsi
	jne	LBB0_2
	movq	%rax, __t3Gcd1p(%rip)
	retq
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	$1, %edi
	movl	$1, %esi
	callq	__t3Gcd3GCD
	leaq	l_formatString(%rip), %rbx
	movq	%rbx, %rdi
	movq	%rax, %rsi
	callq	_printf
	movq	__t3Gcd1p(%rip), %rsi
	movq	%rbx, %rdi
	callq	_printf
	movl	$1, %eax
	popq	%rbx
	retq
	.cfi_endproc

	.globl	__t3Gcd1x
.zerofill __DATA,__common,__t3Gcd1x,8,3
	.globl	__t3Gcd1p
.zerofill __DATA,__common,__t3Gcd1p,16,3
	.section	__TEXT,__const
l_formatString:
	.asciz	"c:%d"

.subsections_via_symbols
