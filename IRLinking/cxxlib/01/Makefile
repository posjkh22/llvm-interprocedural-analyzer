
run:
	lli result.bc

all:
	clang++ -S -emit-llvm -o test.bc test.cpp
	clang++ -S -emit-llvm -o func1.bc func1.cpp
	llvm-link -o result.bc func1.bc test.bc

clean:
	*.bc
