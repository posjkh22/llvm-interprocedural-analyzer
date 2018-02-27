/* No error Case */

typedef struct file {

	int a;

}FILE;

int a = 0;
FILE g_file;

FILE *fopen(char *in, char *mod);
void fclose(FILE *in);
void fnc1(FILE* fin1, FILE* fin2);
void fnc2(FILE* fin1, FILE* fin2);
void fnc3(FILE *fin2);

FILE *fopen(char *in, char *mod){

	a++;

	return &g_file;
}

void fclose(FILE *in){

	a--;
}

void fnc3(FILE *fin2){

	fclose(fin2);

}

void fnc2(FILE* fin1, FILE* fin2){

	fclose(fin1);
	fnc3(fin2);
}

void fnc1(FILE* fin1, FILE* fin2){
	int a = 1;
	fin2  = fopen("file.in", "r");
	fnc2(fin1, fin2);
}
	
int main(){

	FILE *fin1  = fopen("file.in", "r");
	FILE *fin2;

	fnc1(fin1, fin2);


	a = 0;

	return 0;

}
