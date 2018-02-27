
all:
	clang -S -emit-llvm -o check5-5.bc check5-5.c
	ld.gold --plugin /home/posjkh/LLVM/llvm-ubuntu-linux-5.0/lib/libLTO.so \
		-plugin-opt -emit-llvm check5-5.bc -o result.bc

##opt -O3 -o opt_check4.bc check4.bc

clean:
	rm *.bc
