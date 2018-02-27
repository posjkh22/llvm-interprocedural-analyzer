
/* Not Error Case */

#include <stdlib.h>

int gv = 1;
int a = 0;



int *fnc1(int *ptr1){

	int *a = ptr1;
	return a;
}

int *fnc2(int *ptr2, int *ptr3){

	return ptr2;
}

void fnc3(int *ptr2, int *ptr3){

	int a = 0;
	free(ptr2);
	free(ptr3);

}


int main(){

	int *ptr1 = (int *)malloc(sizeof(int));
	int *ptr2 = (int *)malloc(sizeof(int));
	int *ptr3 = (int *)malloc(sizeof(int));

	int *returnPtr;

	returnPtr = fnc1(ptr1);
	free(returnPtr);
	
	returnPtr = fnc2(ptr2, ptr3);
	returnPtr = fnc2(ptr2, ptr3);
	
	fnc3(returnPtr, ptr3);

	return 0;

}
