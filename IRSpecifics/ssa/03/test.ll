; ModuleID = 'test.bc'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32*, align 8
  %8 = alloca i32*, align 8
  %9 = alloca i32*, align 8
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  store i32 2, i32* %3, align 4
  store i32 4, i32* %4, align 4
  store i32 3, i32* %5, align 4
  store i32 5, i32* %6, align 4
  store i32* %3, i32** %7, align 8
  %10 = load i32, i32* %3, align 4
  store i32 %10, i32* %2, align 4
  %11 = load i32, i32* %3, align 4
  store i32 %11, i32* %5, align 4
  store i32* %4, i32** %9, align 8
  %12 = load i32*, i32** %9, align 8
  %13 = load i32, i32* %12, align 4
  %14 = icmp eq i32 %13, 10
  br i1 %14, label %15, label %20

; <label>:15:                                     ; preds = %0
  %16 = load i32, i32* %4, align 4
  %17 = load i32*, i32** %7, align 8
  store i32 %16, i32* %17, align 4
  %18 = load i32, i32* %2, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %2, align 4
  br label %23

; <label>:20:                                     ; preds = %0
  %21 = load i32, i32* %4, align 4
  %22 = load i32*, i32** %7, align 8
  store i32 %21, i32* %22, align 4
  br label %23

; <label>:23:                                     ; preds = %20, %15
  store i32* %2, i32** %8, align 8
  %24 = load i32*, i32** %7, align 8
  %25 = load i32, i32* %24, align 4
  %26 = load i32*, i32** %8, align 8
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %27, %25
  store i32 %28, i32* %26, align 4
  %29 = load i32, i32* %5, align 4
  %30 = load i32*, i32** %8, align 8
  %31 = load i32, i32* %30, align 4
  %32 = add nsw i32 %31, %29
  store i32 %32, i32* %30, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 5.0.0 (tags/RELEASE_500/final)"}
