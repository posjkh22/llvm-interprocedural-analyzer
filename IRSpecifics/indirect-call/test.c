
#include <stdio.h>

void func(int a, int b){

	printf("result: %d\n", a+b);
}


int main(){

	void (*func_ptr)(int, int);

	func(1, 2);

	func_ptr = func;


	func_ptr(3, 5);


	return 0;
}
