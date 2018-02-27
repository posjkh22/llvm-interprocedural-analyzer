
bc:
	clang -cc1 -emit-llvm -o test.bc test.c

opt:
	opt -mem2reg test.bc -o test.opt.bc
	llvm-dis test.opt.bc

clean:	
	rm -f test.bc *.ll
