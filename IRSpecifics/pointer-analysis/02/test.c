
#include <stdio.h>

int main(){

	int a;
	int b;
	int c;

	a = 1;
	b = 2;
	c = 3;

	a = b; 
	//a = 2;
	//b = 2;
	//c = 3;
	b = c;
	//a = 2;
	//b = 3;
	//c = 3;
	c = a;
	//a = 2;
	//b = 3;
	//c = 2;
	

	return 0;

}
