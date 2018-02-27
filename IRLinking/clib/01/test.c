
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func1.h"

int main(){
	
	int *a = (int*)malloc(sizeof(int));

	char* str1 = "hello";
	char* str2 = "hello";

	if(!strcmp(str1, str2)){

		printf("same!\n");
	}

	func1(1, 2);

	return 0;

}
