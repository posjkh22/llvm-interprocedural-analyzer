
#include <stdlib.h>

int a = 0;
FILE g_file;



void fnc1(FILE* fin){

	fclose(fin);
	fclose(fin);

}

int main(){

	FILE *fin  = fopen("file.in", "r");

	fnc1(fin);

	a = 0;

	return 0;

}
