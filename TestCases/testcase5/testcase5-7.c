
/* Not free Error Case */

#include <stdlib.h>

int gv = 1;
int a = 0;


int main(){

	int *ptr1 = (int *)malloc(sizeof(int));

	int a = 0;

	if(a == 0){

		a = 1;

	}else{

		free(ptr1);

	}


	return 0;

}
