


int func1(int a, int b){

	int x = a;
	int y = b;

	return x+y;
}


int func2(int a, int b){

	return a+b;
}



int main(){

	int a = 1;
	int b = 9;

	int c;

	c = func1(a, b);

	c = func2(a, b);

	return 0;
}
