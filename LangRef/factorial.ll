
;// Precondition: val is non-negative.
;int factorial1(int val) { if (val == 0)
    ;return 1;
    ;return val * factorial1(val - 1);
;}
; Precondition: %val is non-negative.
define i32 @factorial1(i32 %val)
{
    %is_base_case = icmp eq i32 %val, 0
    br i1 %is_base_case, label %base_case, label %recursive_case
    base_case:
    ret i32 1
    recursive_case:
    %1 = add i32 -1,%val
    %2 = call i32 @factorial1(i32 %1);
    %3 = mul i32 %val, %2
    ret i32 %3
}


;int factorial(int val) {
    ;int temp = 1;
    ;for (int i = 2; i <= val; ++i)
    ;temp *= i; 
    ;return temp;
;}
; Precondition: %val is non-negative.
define i32 @factorial2(i32 %val)
{
    entry:
    
    br label %check_for_condition
    
    check_for_condition:
    %current_i = phi i32 [2, %entry], [%i_plus_one,%for_body]
    %temp = phi i32 [1,%entry],[%new_temp,%for_body]
    %i_leq_val = icmp sle i32 %current_i, %val
    br i1 %i_leq_val, label %for_body,label %end_loop
    
    for_body:
    %new_temp = mul i32 %temp,%current_i
    %i_plus_one = add i32 %current_i,1
    br label %check_for_condition
    
    end_loop:
    ret i32 %temp
}

;int factorial(int val) {
    ;int temp = 1;
    ;for (int i = 2; i <= val; ++i)
    ;temp *= i; 
    ;return temp;
;}
; Precondition: %val is non-negative.
define i32 @factorial3(i32 %val)
{
    entry:
    %i.addr = alloca i32
    %temp.addr1 = alloca i32
    store i32 2, i32* %i.addr
    store i32 1, i32 * %temp.addr1
    br label %check_for_condition
    
    check_for_condition:
    %current_i  = load i32, i32* %i.addr
    %temp       = load i32, i32* %temp.addr1
    %i_leq_val  = icmp sle i32 %current_i, %val
    br i1 %i_leq_val, label %for_body, label %end_loop
    
    for_body:
    %i_plus_one = add i32 %current_i,1
    %new_temp = mul i32 %temp, %current_i
    store i32 %i_plus_one, i32* %i.addr
    store i32 %new_temp, i32* %temp.addr1
    br label %check_for_condition
    br label %check_for_condition
    
    end_loop:
    ret i32 %temp
}


@formatString = private constant [5 x i8] c"c:%d\00" 
define i32 @main(i32 %argc, i8** %argv)
{
    %1 = call i32 @factorial3(i32 4)
    %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @formatString , i32 0, i32 0), i32 %1)
    %2 = mul i32 %1, 7
    %3 = icmp eq i32 %2, 42
    %result = zext i1 %3 to i32
    ret i32 %result
}


declare i32 @printf(i8*, ...) #1

