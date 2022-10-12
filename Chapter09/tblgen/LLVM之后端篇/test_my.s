	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.globl	_test                           ## -- Begin function test
	.p2align	4, 0x90
_test:                                  ## @test
	.cfi_startproc
## %bb.0:
	movl	$1, %eax
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
