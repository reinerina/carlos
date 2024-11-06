@.str.in.int = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.in.float = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.in.char = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.in.bool = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.out.int = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.out.float = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.out.char = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.out.bool = private unnamed_addr constant [3 x i8] c"%d\00", align 1
declare i32 @scanf(i8*, ...)
declare i32 @printf(i8*, ...)
define i32 @main() {
entry:
%1 = add i32 0, 0
%x0 = alloca i32
store i32 %1, i32* %x0
%2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %x0)
%3 = add i32 0, 1
%a0 = alloca i32
store i32 %3, i32* %a0
%4 = add i32 0, 1
%b0 = alloca i32
store i32 %4, i32* %b0
%5 = add i32 0, 0
%6 = load i32, i32* %x0
%i0 = alloca i32
%7 = sub i32 %5, 1
store i32 %7, i32* %i0
br label %for1.cond
for1.cond:
%8 = load i32, i32* %i0
%9 = add i32 %8, 1
store i32 %9, i32* %i0
%10 = load i32, i32* %i0
%11 = icmp slt i32 %10, %6
br i1 %11, label %for1.body, label %for1.end
for1.body:
%12 = load i32, i32* %a0
%i1 = alloca i32
store i32 %12, i32* %i1
%13 = add i8 0, 32
%14 = load i32, i32* %i1
%15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %13)
%16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %14)
%17 = load i32, i32* %a0
%18 = load i32, i32* %b0
%19 = add i32 %17, %18
store i32 %19, i32* %a0
br label %for1.cond
for1.end:
%20 = load i32, i32* %a0
%a1 = alloca i32
store i32 %20, i32* %a1
%21 = add i8 0, 10
%22 = load i32, i32* %a1
%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %21)
%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %22)
ret i32 0
}
