; ModuleID = '/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter07/tinylang/examples/Gcd.mod'
source_filename = "/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter07/tinylang/examples/Gcd.mod"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-darwin21.5.0"

%Point = type { i64, i64 }

@_t3Gcd1x = global i64 0, !dbg !0
@_t3Gcd1p = global %Point zeroinitializer, !dbg !4
@formatString = private constant [5 x i8] c"c:%d\00"

define i64 @_t3Gcd3GCD(i64 %a, i64 %b) !dbg !9 {
entry:
  call void @llvm.dbg.value(metadata i64 %a, metadata !12, metadata !DIExpression()), !dbg !13
  call void @llvm.dbg.value(metadata i64 %b, metadata !14, metadata !DIExpression()), !dbg !15
  %0 = icmp eq i64 %b, 0
  br i1 %0, label %if.body, label %while.cond

if.body:                                          ; preds = %entry
  ret i64 %a

while.cond:                                       ; preds = %while.body, %entry
  %1 = phi i64 [ %2, %while.body ], [ %a, %entry ]
  %2 = phi i64 [ %4, %while.body ], [ %b, %entry ]
  %3 = icmp ne i64 %2, 0
  br i1 %3, label %while.body, label %after.while

while.body:                                       ; preds = %while.cond
  %4 = srem i64 %1, %2
  br label %while.cond

after.while:                                      ; preds = %while.cond
  store i64 %1, i64* getelementptr inbounds (%Point, %Point* @_t3Gcd1p, i32 0, i32 0), align 8
  ret i64 %1
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata %0, metadata %1, metadata %2) #0

define i64 @main() {
entry:
  %0 = call i64 @_t3Gcd3GCD(i64 1, i64 1)
  %formatStringPtr = getelementptr inbounds [5 x i8], [5 x i8]* @formatString, i32 0, i32 0
  %1 = call i32 @printf(i8* %formatStringPtr, i64 %0)
  %t3Gcd1p_ptrInst = getelementptr inbounds %Point, %Point* @_t3Gcd1p, i32 0, i32 0
  %t3Gcd1p_ptrInst_loadInst = load i64, i64* %t3Gcd1p_ptrInst, align 8
  %2 = call i32 @printf(i8* %formatStringPtr, i64 %t3Gcd1p_ptrInst_loadInst)
  ret i64 1
}

declare i32 @printf(i8* %0, i64 %1)

attributes #0 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!6}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", linkageName: "_t3Gcd1x", scope: !2, file: !2, line: 5, type: !3, isLocal: false, isDefinition: true)
!2 = !DIFile(filename: "Gcd.mod", directory: "/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter07/tinylang/examples")
!3 = !DIBasicType(name: "INTEGER", size: 64, encoding: DW_ATE_signed)
!4 = !DIGlobalVariableExpression(var: !5, expr: !DIExpression())
!5 = distinct !DIGlobalVariable(name: "p", linkageName: "_t3Gcd1p", scope: !2, file: !2, line: 6, isLocal: false, isDefinition: true)
!6 = distinct !DICompileUnit(language: DW_LANG_Modula2, file: !2, producer: "tinylang", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !7, globals: !8)
!7 = !{}
!8 = !{!0, !4}
!9 = distinct !DISubprogram(name: "GCD", linkageName: "_t3Gcd3GCD", scope: !2, file: !2, line: 8, type: !10, scopeLine: 8, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !6, retainedNodes: !7)
!10 = !DISubroutineType(types: !11)
!11 = !{!3, !3, !3}
!12 = !DILocalVariable(name: "a", arg: 1, scope: !9, file: !2, line: 8, type: !3)
!13 = !DILocation(line: 8, column: 15, scope: !9)
!14 = !DILocalVariable(name: "b", arg: 2, scope: !9, file: !2, line: 8, type: !3)
!15 = !DILocation(line: 8, column: 18, scope: !9)
