
run:
	lli test.bc
	

all: 
	clang++ -fno-use-cxa-atexit -S -emit-llvm -o test.bc test.cpp

#	llvm-link -disable-lazy-loading -o result.bc test.bc


clean:
	rm -f *.bc *.s
