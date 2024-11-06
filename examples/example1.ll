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
%amount0 = alloca i32
store i32 %1, i32* %amount0
%2 = alloca [7 x i32]
%3 = add i32 0, 100
%4 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 0
store i32 %3, i32* %4
%5 = add i32 0, 50
%6 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 1
store i32 %5, i32* %6
%7 = add i32 0, 20
%8 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 2
store i32 %7, i32* %8
%9 = add i32 0, 10
%10 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 3
store i32 %9, i32* %10
%11 = add i32 0, 5
%12 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 4
store i32 %11, i32* %12
%13 = add i32 0, 2
%14 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 5
store i32 %13, i32* %14
%15 = add i32 0, 1
%16 = getelementptr inbounds [7 x i32], [7 x i32]* %2, i32 0, i32 6
store i32 %15, i32* %16
%17 = alloca [7 x i32]*
store [7 x i32]* %2, [7 x i32]** %17
%bills0 = load [7 x i32]*, [7 x i32]** %17
%18 = alloca [7 x i32]
%19 = add i32 0, 0
%20 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 0
store i32 %19, i32* %20
%21 = add i32 0, 0
%22 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 1
store i32 %21, i32* %22
%23 = add i32 0, 0
%24 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 2
store i32 %23, i32* %24
%25 = add i32 0, 0
%26 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 3
store i32 %25, i32* %26
%27 = add i32 0, 0
%28 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 4
store i32 %27, i32* %28
%29 = add i32 0, 0
%30 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 5
store i32 %29, i32* %30
%31 = add i32 0, 0
%32 = getelementptr inbounds [7 x i32], [7 x i32]* %18, i32 0, i32 6
store i32 %31, i32* %32
%33 = alloca [7 x i32]*
store [7 x i32]* %18, [7 x i32]** %33
%n_bills0 = load [7 x i32]*, [7 x i32]** %33
%34 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %amount0)
%35 = add i32 0, 0
%36 = add i32 0, 7
%i0 = alloca i32
%37 = sub i32 %35, 1
store i32 %37, i32* %i0
br label %for1.cond
for1.cond:
%38 = load i32, i32* %i0
%39 = add i32 %38, 1
store i32 %39, i32* %i0
%40 = load i32, i32* %i0
%41 = icmp slt i32 %40, %36
br i1 %41, label %for1.body, label %for1.end
for1.body:
%42 = load i32, i32* %amount0
%43 = load i32, i32* %i0
%44 = add i32 0, %43
%45 = getelementptr inbounds [7 x i32], [7 x i32]* %bills0, i32 0, i32 %44
%46 = load i32, i32* %45
%47 = sdiv i32 %42, %46
%48 = load i32, i32* %i0
%49 = add i32 0, %48
%50 = getelementptr inbounds [7 x i32], [7 x i32]* %n_bills0, i32 0, i32 %49
store i32 %47, i32* %50
%51 = load i32, i32* %amount0
%52 = load i32, i32* %i0
%53 = add i32 0, %52
%54 = getelementptr inbounds [7 x i32], [7 x i32]* %bills0, i32 0, i32 %53
%55 = load i32, i32* %54
%56 = srem i32 %51, %55
store i32 %56, i32* %amount0
%57 = load i32, i32* %amount0
%58 = add i32 0, 0
%59 = icmp eq i32 %57, %58
br i1 %59, label %if1.then, label %if1.end
if1.then:
br label %for1.end
if1.end:
br label %for1.cond
for1.end:
%60 = add i32 0, 0
%61 = add i32 0, 7
%i1 = alloca i32
%62 = sub i32 %60, 1
store i32 %62, i32* %i1
br label %for2.cond
for2.cond:
%63 = load i32, i32* %i1
%64 = add i32 %63, 1
store i32 %64, i32* %i1
%65 = load i32, i32* %i1
%66 = icmp slt i32 %65, %61
br i1 %66, label %for2.body, label %for2.end
for2.body:
%67 = load i32, i32* %i1
%68 = add i32 0, %67
%69 = getelementptr inbounds [7 x i32], [7 x i32]* %n_bills0, i32 0, i32 %68
%70 = load i32, i32* %69
%71 = add i8 0, 32
%72 = add i8 0, 120
%73 = add i8 0, 32
%74 = load i32, i32* %i1
%75 = add i32 0, %74
%76 = getelementptr inbounds [7 x i32], [7 x i32]* %bills0, i32 0, i32 %75
%77 = load i32, i32* %76
%78 = add i8 0, 10
%79 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %70)
%80 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %71)
%81 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %72)
%82 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %73)
%83 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %77)
%84 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %78)
br label %for2.cond
for2.end:
ret i32 0
}
