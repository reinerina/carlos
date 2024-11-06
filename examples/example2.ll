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
%n0 = alloca i32
store i32 %1, i32* %n0
%2 = fadd float 0.0, 3.00000
%pi0 = alloca float
store float %2, float* %pi0
%3 = fadd float 0.0, 1.00000
%sign0 = alloca float
store float %3, float* %sign0
%4 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.in.int, i32 0), i32* %n0)
%5 = add i32 0, 0
%6 = load i32, i32* %n0
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
%12 = load i32, i32* %i0
%13 = sitofp i32 %12 to float
%14 = fadd float 0.0, 1.00000
%15 = fadd float %13, %14
%16 = fadd float 0.0, 2.00000
%17 = fmul float %15, %16
%i1 = alloca float
store float %17, float* %i1
%18 = fadd float 0.0, 4.00000
%19 = load float, float* %i1
%20 = load float, float* %i1
%21 = fadd float 0.0, 1.00000
%22 = fadd float %20, %21
%23 = fmul float %19, %22
%24 = load float, float* %i1
%25 = fadd float 0.0, 2.00000
%26 = fadd float %24, %25
%27 = fmul float %23, %26
%28 = fdiv float %18, %27
%term0 = alloca float
store float %28, float* %term0
%29 = load float, float* %pi0
%30 = load float, float* %sign0
%31 = load float, float* %term0
%32 = fmul float %30, %31
%33 = fadd float %29, %32
store float %33, float* %pi0
%34 = load float, float* %sign0
%35 = fadd float 0.0, -1.00000
%36 = fmul float %34, %35
store float %36, float* %sign0
br label %for1.cond
for1.end:
%37 = add i8 0, 10
%38 = load float, float* %pi0
%39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.char, i32 0), i8 %37)
%40 = fpext float %38 to double
%41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.out.float, i32 0), double %40)
ret i32 0
}
