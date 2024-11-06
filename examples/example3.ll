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
%1 = alloca [14 x i32]
%2 = add i32 0, 0
%3 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 0
store i32 %2, i32* %3
%4 = add i32 0, 0
%5 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 1
store i32 %4, i32* %5
%6 = add i32 0, 0
%7 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 2
store i32 %6, i32* %7
%8 = add i32 0, 0
%9 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 3
store i32 %8, i32* %9
%10 = add i32 0, 0
%11 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 4
store i32 %10, i32* %11
%12 = add i32 0, 0
%13 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 5
store i32 %12, i32* %13
%14 = add i32 0, 0
%15 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 6
store i32 %14, i32* %15
%16 = add i32 0, 0
%17 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 7
store i32 %16, i32* %17
%18 = add i32 0, 0
%19 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 8
store i32 %18, i32* %19
%20 = add i32 0, 0
%21 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 9
store i32 %20, i32* %21
%22 = add i32 0, 0
%23 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 10
store i32 %22, i32* %23
%24 = add i32 0, 0
%25 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 11
store i32 %24, i32* %25
%26 = add i32 0, 0
%27 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 12
store i32 %26, i32* %27
%28 = add i32 0, 0
%29 = getelementptr inbounds [14 x i32], [14 x i32]* %1, i32 0, i32 13
store i32 %28, i32* %29
%30 = alloca [14 x i32]*
store [14 x i32]* %1, [14 x i32]** %30
%a0 = load [14 x i32]*, [14 x i32]** %30
%31 = add i32 0, 0
%32 = add i32 0, 7
%i0 = alloca i32
%33 = sub i32 %31, 1
store i32 %33, i32* %i0
br label %for1.cond
for1.cond:
%34 = load i32, i32* %i0
%35 = add i32 %34, 1
store i32 %35, i32* %i0
%36 = load i32, i32* %i0
%37 = icmp slt i32 %36, %32
br i1 %37, label %for1.body, label %for1.end
for1.body:
%38 = add i32 0, 0
%39 = add i32 0, 2
%j0 = alloca i32
%40 = sub i32 %38, 1
store i32 %40, i32* %j0
br label %for2.cond
for2.cond:
%41 = load i32, i32* %j0
%42 = add i32 %41, 1
store i32 %42, i32* %j0
%43 = load i32, i32* %j0
%44 = icmp slt i32 %43, %39
br i1 %44, label %for2.body, label %for2.end
for2.body:
%45 = load i32, i32* %i0
%46 = mul i32 %45, 2
%47 = add i32 0, %46
%48 = load i32, i32* %j0
%49 = add i32 %47, %48
%50 = getelementptr inbounds [14 x i32], [14 x i32]* %a0, i32 0, i32 %49
%51 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %50)
br label %for2.cond
for2.end:
br label %for1.cond
for1.end:
%52 = add i32 0, 0
%53 = add i32 0, 7
%i1 = alloca i32
%54 = sub i32 %52, 1
store i32 %54, i32* %i1
br label %for3.cond
for3.cond:
%55 = load i32, i32* %i1
%56 = add i32 %55, 1
store i32 %56, i32* %i1
%57 = load i32, i32* %i1
%58 = icmp slt i32 %57, %53
br i1 %58, label %for3.body, label %for3.end
for3.body:
%59 = add i32 0, 0
%60 = add i32 0, 2
%j1 = alloca i32
%61 = sub i32 %59, 1
store i32 %61, i32* %j1
br label %for4.cond
for4.cond:
%62 = load i32, i32* %j1
%63 = add i32 %62, 1
store i32 %63, i32* %j1
%64 = load i32, i32* %j1
%65 = icmp slt i32 %64, %60
br i1 %65, label %for4.body, label %for4.end
for4.body:
%66 = load i32, i32* %i1
%67 = mul i32 %66, 2
%68 = add i32 0, %67
%69 = load i32, i32* %j1
%70 = add i32 %68, %69
%71 = getelementptr inbounds [14 x i32], [14 x i32]* %a0, i32 0, i32 %70
%72 = load i32, i32* %71
%73 = add i8 0, 32
%74 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.int, i32 0), i32 %72)
%75 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %73)
br label %for4.cond
for4.end:
%76 = add i8 0, 10
%77 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %76)
br label %for3.cond
for3.end:
ret i32 0
}
