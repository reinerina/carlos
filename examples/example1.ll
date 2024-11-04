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
%2 = add i32 0, 10
%x0 = alloca i32
store i32 %1, i32* %x0
br label %for1.cond
for1.cond:
%3 = load i32, i32* %x0
%4 = icmp slt i32 %3, %2
br i1 %4, label %for1.body, label %for1.end
for1.body:
%5 = load i32, i32* %x0
%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %5)
%7 = load i32, i32* %x0
%8 = add i32 %7, 1
store i32 %8, i32* %x0
br label %for1.cond
for1.end:
ret i32 0
}
