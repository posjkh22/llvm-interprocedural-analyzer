
/* 2018-02-07 */
/* Top-level variable pointer analysis */

#include <stdlib.h>
#include <stdio.h>

int main(){

	int *a;
	int *b;
	int c;
	int *d;

	a = (int*)malloc(sizeof(int));

	*a = 5;

	b = a;

	printf("value : %d", *b);
	

	c = *b;

	printf("value : %d", c);

	c = c+1;
	
	printf("value : %d", c);

	d = a;
	
	printf("value : %d", *d);

	d = (int*)malloc(sizeof(int));

	if(c ==5){

		b = a;

	}else{

		b = d;
		*b = 7;
	}
	
	printf("value : %d", *b);

	return 0;

}
