target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-darwin21.5.0"

declare i32 @printf(i8*, ...)
                i8* getelementptr inbounds ([13 x i8],
                        [13 x i8]* @hellostr, i64 0, i64 0))