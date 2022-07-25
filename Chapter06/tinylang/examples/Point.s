	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.globl	__t5Point7AssignX
	.p2align	4, 0x90
__t5Point7AssignX:
	.cfi_startproc
	movq	%rdi, l__t5Point1p(%rip)
	retq
	.cfi_endproc

	.globl	__t5Point8GetColor
	.p2align	4, 0x90
__t5Point8GetColor:
	.cfi_startproc
	retq
	.cfi_endproc

.zerofill __DATA,__bss,l__t5Point1p,16,3
.subsections_via_symbols
