
/* Not Error Case */

#include <stdlib.h>

int gv = 1;
int a = 0;

int *fnc1(int *ptr){

	int *a = ptr;
	return a;
}


int main(){

	int *ptr = (int *)malloc(sizeof(int));
	int *returnPtr;

	returnPtr = fnc1(ptr);

	free(returnPtr);
	return 0;

}
