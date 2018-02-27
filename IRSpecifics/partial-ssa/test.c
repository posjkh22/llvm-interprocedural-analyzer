
int main(){

	int a = 1;
	int b = 2;
	int c = 3;

	int *x_ptr;
	int *y_ptr;
	int *z_ptr;


	x_ptr = &a;
	y_ptr = &b;
	z_ptr = &c;

	a = 10;
	b = 20;
	c = 30;

	x_ptr = &c;
	y_ptr = &b;
	z_ptr = &a;



	return 0;
}
