
bc:
	clang -Xclang -disable-O0-optnone -emit-llvm -o test.bc -c test.c
	llvm-dis test.bc

opt:
	opt -mem2reg -S test.ll -o test-mem2reg.ll

clean:
	rm -f test.bc
