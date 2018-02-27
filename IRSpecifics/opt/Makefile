
bc:
	clang -S -emit-llvm -o test.bc test.c

opt:
	opt -S -O0 -o test0.bc test.bc
	opt -S -O1 -o test1.bc test.bc
	opt -S -O2 -o test2.bc test.bc
	opt -S -O3 -o test3.bc test.bc

clean:
	rm -f test.bc
