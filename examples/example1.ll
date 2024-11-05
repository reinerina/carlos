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
%1 = alloca [9 x i1]
%2 = add i1 0, 0
%3 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 0
store i1 %2, i1* %3
%4 = add i1 0, 0
%5 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 1
store i1 %4, i1* %5
%6 = add i1 0, 0
%7 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 2
store i1 %6, i1* %7
%8 = add i1 0, 0
%9 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 3
store i1 %8, i1* %9
%10 = add i1 0, 0
%11 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 4
store i1 %10, i1* %11
%12 = add i1 0, 0
%13 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 5
store i1 %12, i1* %13
%14 = add i1 0, 0
%15 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 6
store i1 %14, i1* %15
%16 = add i1 0, 0
%17 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 7
store i1 %16, i1* %17
%18 = add i1 0, 0
%19 = getelementptr inbounds [9 x i1], [9 x i1]* %1, i32 0, i32 8
store i1 %18, i1* %19
%20 = alloca [9 x i1]*
store [9 x i1]* %1, [9 x i1]** %20
%x0= load [9 x i1]*, [9 x i1]** %20
%21 = add i1 0, 1
%22 = add i32 0, 2
%23 = mul i32 %22, 3
%24 = add i32 0, %23
%25 = add i32 0, 1
%26 = add i32 %24, %25
%27 = getelementptr inbounds [9 x i1], [9 x i1]* %x0, i32 0, i32 %26
store i1 %21, i1* %27
%28 = add i32 0, 0
%29 = add i32 0, 3
%i0 = alloca i32
store i32 %28, i32* %i0
br label %for1.cond
for1.cond:
%30 = load i32, i32* %i0
%31 = icmp slt i32 %30, %29
br i1 %31, label %for1.body, label %for1.end
for1.body:
%32 = add i32 0, 0
%33 = add i32 0, 3
%j0 = alloca i32
store i32 %32, i32* %j0
br label %for2.cond
for2.cond:
%34 = load i32, i32* %j0
%35 = icmp slt i32 %34, %33
br i1 %35, label %for2.body, label %for2.end
for2.body:
%36 = load i32, i32* %i0
%37 = mul i32 %36, 3
%38 = add i32 0, %37
%39 = load i32, i32* %j0
%40 = add i32 %38, %39
%41 = getelementptr inbounds [9 x i1], [9 x i1]* %x0, i32 0, i32 %40
%42 = load i1, i1* %41
%43 = add i1 0, 1
%44 = icmp eq i1 %42, %43
br i1 %44, label %if1.then, label %if1.else
if1.then:
%45 = add i8 0, 88
%46 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %45)
br label %for2.cond
%47 = add i8 0, 89
%48 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %47)
br label %if1.end
if1.else:
%49 = add i8 0, 79
%50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %49)
br label %if1.end
if1.end:
%51 = load i32, i32* %j0
%52 = add i32 %51, 1
store i32 %52, i32* %j0
br label %for2.cond
for2.end:
%53 = add i8 0, 10
%54 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %53)
%55 = load i32, i32* %i0
%56 = add i32 %55, 1
store i32 %56, i32* %i0
br label %for1.cond
for1.end:
ret i32 0
}
