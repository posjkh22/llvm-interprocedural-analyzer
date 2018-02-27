
/* Double Free Error Case */

#include <stdlib.h>

int gv = 1;
int a = 0;


int fnc1(int *ptr){

	free(ptr);
	free(ptr);

	return 0;
}


int main(){

	int *ptr = (int *)malloc(sizeof(int));

	fnc1(ptr);

	return 0;

}
