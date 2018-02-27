
run:
	lli result.bc

all:
	clang -static -S -emit-llvm -o test.bc test.c
	clang -static -S -emit-llvm -o func1.bc func1.c
	llvm-link -disable-lazy-loading -o result.bc func1.bc test.bc

clean:
	rm -f *.bc
