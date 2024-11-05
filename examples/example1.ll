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
%12 = load i32, i32* %x0
%13 = add i32 0, 2
%14 = icmp sgt i32 %12, %13
br i1 %14, label %if1.then, label %if1.else
if1.then:
%15 = add i8 0, 72
%16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %15)
br label %for1.end
if1.else:
%17 = load i32, i32* %x0
%18 = add i32 0, 0
%19 = icmp slt i32 %17, %18
br i1 %19, label %if2.then, label %if2.else
if2.then:
%20 = add i8 0, 69
%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %20)
br label %if1.end
if2.else:
%22 = add i8 0, 76
%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %22)
br label %if1.end
if1.end:
br label %for1.cond
for1.end:
ret i32 0
}
