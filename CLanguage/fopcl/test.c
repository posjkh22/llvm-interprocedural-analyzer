#include <stdio.h>

int main(){

	FILE *fin1 = fopen("hello", "r");
	FILE *fin2 = fopen("hello", "r");
	FILE *fin3 = fopen("out", "w");

	char str1[20];
	char str2[20];

	fscanf(fin1, "%s", str1);
	fscanf(fin2, "%s", str2);

	fprintf(fin3, "%s\n", str1);
	fprintf(fin3, "%s\n", str2);

	fclose(fin1);
	fclose(fin2);

	return 0;
}
