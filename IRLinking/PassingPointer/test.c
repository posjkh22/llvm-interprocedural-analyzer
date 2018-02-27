
int x =0;

int func(int *a, int b){

	int c = *a;

	(*a) = 5;

	return c + b;
}

int main(){

	int a = 0;
	int b = 1;

	int c = func(&a, b);


}
