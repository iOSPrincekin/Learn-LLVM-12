	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0
	.file	1 "/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter07/tinylang/examples/Gcd.mod"
	.globl	__t3Gcd3GCD
	.p2align	4, 0x90
__t3Gcd3GCD:
Lfunc_begin0:
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
Lfunc_end0:
	.cfi_endproc

	.globl	_main
	.p2align	4, 0x90
_main:
Lfunc_begin1:
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
Lfunc_end1:
	.cfi_endproc

	.globl	__t3Gcd1x
.zerofill __DATA,__common,__t3Gcd1x,8,3
	.globl	__t3Gcd1p
.zerofill __DATA,__common,__t3Gcd1p,16,3
	.section	__TEXT,__const
l_formatString:
	.asciz	"c:%d"

	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1
	.byte	17
	.byte	1
	.byte	37
	.byte	14
	.byte	19
	.byte	5
	.byte	3
	.byte	14
	.byte	16
	.byte	23
	.byte	27
	.byte	14
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.byte	0
	.byte	0
	.byte	2
	.byte	52
	.byte	0
	.byte	3
	.byte	14
	.byte	73
	.byte	19
	.byte	63
	.byte	25
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	2
	.byte	24
	.byte	110
	.byte	14
	.byte	0
	.byte	0
	.byte	3
	.byte	36
	.byte	0
	.byte	3
	.byte	14
	.byte	62
	.byte	11
	.byte	11
	.byte	11
	.byte	0
	.byte	0
	.byte	4
	.byte	52
	.byte	0
	.byte	3
	.byte	14
	.byte	63
	.byte	25
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	2
	.byte	24
	.byte	110
	.byte	14
	.byte	0
	.byte	0
	.byte	5
	.byte	46
	.byte	0
	.byte	17
	.byte	1
	.byte	18
	.byte	6
	.ascii	"\347\177"
	.byte	25
	.byte	64
	.byte	24
	.byte	110
	.byte	14
	.byte	3
	.byte	14
	.byte	58
	.byte	11
	.byte	59
	.byte	11
	.byte	73
	.byte	19
	.byte	63
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
.set Lset0, Ldebug_info_end0-Ldebug_info_start0
	.long	Lset0
Ldebug_info_start0:
	.short	4
.set Lset1, Lsection_abbrev-Lsection_abbrev
	.long	Lset1
	.byte	8
	.byte	1
	.long	0
	.short	10
	.long	9
.set Lset2, Lline_table_start0-Lsection_line
	.long	Lset2
	.long	17
	.quad	Lfunc_begin0
.set Lset3, Lfunc_end0-Lfunc_begin0
	.long	Lset3
	.byte	2
	.long	101
	.long	67

	.byte	1
	.byte	5
	.byte	9
	.byte	3
	.quad	__t3Gcd1x
	.long	111
	.byte	3
	.long	103
	.byte	5
	.byte	8
	.byte	4
	.long	120

	.byte	1
	.byte	6
	.byte	9
	.byte	3
	.quad	__t3Gcd1p
	.long	122
	.byte	5
	.quad	Lfunc_begin0
.set Lset4, Lfunc_end0-Lfunc_begin0
	.long	Lset4

	.byte	1
	.byte	87
	.long	135
	.long	131
	.byte	1
	.byte	8
	.long	67

	.byte	0
Ldebug_info_end0:
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"tinylang"
	.asciz	"Gcd.mod"
	.asciz	"/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter07/tinylang/examples"
	.asciz	"x"
	.asciz	"INTEGER"
	.asciz	"_t3Gcd1x"
	.asciz	"p"
	.asciz	"_t3Gcd1p"
	.asciz	"GCD"
	.asciz	"_t3Gcd3GCD"
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712
	.short	1
	.short	0
	.long	6
	.long	6
	.long	12
	.long	0
	.long	1
	.short	1
	.short	6
	.long	0
	.long	1
	.long	-1
	.long	2
	.long	3
	.long	5
	.long	-2051494270
	.long	177685
	.long	177693
	.long	-2051494278
	.long	-694245318
	.long	193456595
.set Lset5, LNames4-Lnames_begin
	.long	Lset5
.set Lset6, LNames0-Lnames_begin
	.long	Lset6
.set Lset7, LNames3-Lnames_begin
	.long	Lset7
.set Lset8, LNames1-Lnames_begin
	.long	Lset8
.set Lset9, LNames2-Lnames_begin
	.long	Lset9
.set Lset10, LNames5-Lnames_begin
	.long	Lset10
LNames4:
	.long	111
	.long	1
	.long	42
	.long	0
LNames0:
	.long	120
	.long	1
	.long	74
	.long	0
LNames3:
	.long	101
	.long	1
	.long	42
	.long	0
LNames1:
	.long	122
	.long	1
	.long	74
	.long	0
LNames2:
	.long	135
	.long	1
	.long	95
	.long	0
LNames5:
	.long	131
	.long	1
	.long	95
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712
	.short	1
	.short	0
	.long	1
	.long	0
	.long	12
	.long	0
	.long	1
	.short	1
	.short	6
	.long	-1
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712
	.short	1
	.short	0
	.long	1
	.long	0
	.long	12
	.long	0
	.long	1
	.short	1
	.short	6
	.long	-1
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712
	.short	1
	.short	0
	.long	1
	.long	1
	.long	20
	.long	0
	.long	3
	.short	1
	.short	6
	.short	3
	.short	5
	.short	4
	.short	11
	.long	0
	.long	-1289459405
.set Lset11, Ltypes0-Ltypes_begin
	.long	Lset11
Ltypes0:
	.long	103
	.long	1
	.long	67
	.short	36
	.byte	0
	.long	0
.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
