@helloString = private constant [7 x i8] c"hello\0a\00"
@formatString = private constant [6 x i8] c"c:%d\0a\00"

;[6*i8] array
@array1 = global [6 x i8] zeroinitializer
%MyStruct1 = type { i8, i32, [3 x i32] }
@struct1 = global %MyStruct1 { i8 99, i32 17, [3 x i32] [i32 1, i32 2, i32 3] }

@array2 = global [4 x i8] [i8 0,i8 1,i8 2,i8 3]
@array3 = global [4 x i8] [i8 4,i8 5,i8 6,i8 7]
%MyStruct2 = type { [4 x i8]*,[4 x i8]* }
@struct2 = global %MyStruct2 { [4 x i8]* @array2, [4 x i8]* @array3}

define i32 @main(i32 %argc, i8** %argv)
{
    ;printf
    %call1 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([7 x i8],[7 x i8]* @helloString,i32 0,i32 0))
    
    ;[6*i8] array
    %array1_new_ptr = getelementptr [6 x i8],[6 x i8]* @array1, i32 0
    %array1_elem_ptr = getelementptr [6 x i8],[6 x i8]* @array1, i32 0,i32 0
    %array1_elem_val = load i8, i8* %array1_elem_ptr
    store i8 2, i8* %array1_elem_ptr
    %call2 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i8 %array1_elem_val)
    %array1_elem_val1 = load i8, i8* %array1_elem_ptr
    %call3 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i8 %array1_elem_val1)
    
    ;%MyStruct1 = type < { i8, i32, [3 x i32] }>
    %struct1_new_ptr1 = getelementptr %MyStruct1, %MyStruct1* @struct1, i32 0
    %struct1_new_ptr2 = getelementptr %MyStruct1, %MyStruct1* @struct1, i32 0, i32 0
    %struct1_new_ptr3 = getelementptr %MyStruct1, %MyStruct1* @struct1, i32 0, i32 2,i32 0
    ;%struct1_elem_val1 = load i8, i8* %struct1_new_ptr1
    %struct1_elem_val2 = load i8, i8* %struct1_new_ptr2
    %struct1_elem_val3 = load i32, i32* %struct1_new_ptr3
    ; %call4 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i8 %struct1_elem_val1)
    %call5 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i8 %struct1_elem_val2)
    %call6 = call i32 (i8*,...) @printf(i8* getelementptr inbounds ([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i32 %struct1_elem_val3)
    
    %struct2_new_ptr1 = getelementptr %MyStruct2, %MyStruct2* @struct2,i32 0,i32 1
    %strcut2_loaded_ptr = load [4 x i8]*, [4 x i8]** %struct2_new_ptr1
    %goal1 = getelementptr [4 x i8],[4 x i8]* %strcut2_loaded_ptr,i32 0,i32 1
    %goal2 = load i8,i8* %goal1
    %call7 = call i32 (i8*,...) @printf(i8* getelementptr inbounds([6 x i8],[6 x i8]* @formatString,i32 0,i32 0),i8 %goal2)
    
    ret i32 0
}

declare i32 @printf(i8*, ...) #1
