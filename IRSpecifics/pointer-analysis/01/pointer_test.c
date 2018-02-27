
#include <stdio.h>

int main(){

	int a = 1;
	int *b;
	int **c;
	int ***d;

	b = &a;
	c = &b;
	d = &c;
	
	printf("*b: %d\n", *b);
	printf("**c: %d\n", **c);
	printf("***d: %d\n", ***d);

	b = &d;
	printf("*b: %d\n", *b);
	printf("**c: %d\n", **c);
	printf("***d: %d\n", ***d);

	return 0;

}
