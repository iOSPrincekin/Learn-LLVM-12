	.text
	.file	"test.ll"
	.globl	test                            # -- Begin function test
	.type	test,@function
test:                                   # @test
# %bb.0:
	addi a0, zero, 1
	ret
.Lfunc_end0:
	.size	test, .Lfunc_end0-test
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
