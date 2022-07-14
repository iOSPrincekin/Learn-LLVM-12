%retval = call i32 @test(i32 %argc)
call i32(i8*,...)* @printf(i8* %msg,i32 12,i8 42)   ; yields i32
%X = tail call i32 @foo()                           ; yields i32
%Y = tail call fastcc i32 @foo()                    ; yields i32
call void %foo(i8 97 signext)

%struct.A = type { i32, i8 }
%r = call %struct.A @foo()                          ; yields { i32, i8 }
%gr = extractvalue %struct.A %r,0                   ; yields i32
%gr1 = exractvalue %struct.A %r,1                   ; yields i8
%Z = call void @foo() noreturn                      ; indicates that %foo never returns normally
%ZZ = call zeroext i32 @bar()                       ; Return value is %zeo extended

