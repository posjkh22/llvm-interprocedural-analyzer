
run:
	./test

all: 
	clang++ -S -emit-llvm -o test.bc test.cpp
	llc -o test.s test.bc
	clang++ test.s -o test

clean:
	rm -f *.bc *.s
