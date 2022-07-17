	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 17
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	subl	$12, %esp
Lcfi0:
	.cfi_def_cfa_offset 16
	movl	$L_.str, (%esp)
	calll	_puts
	xorl	%eax, %eax
	addl	$12, %esp
	retl
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"hello world\n"


.subsections_via_symbols
