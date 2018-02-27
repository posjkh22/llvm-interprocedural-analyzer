
void f1();
void f2();
void f3();
int main();

int *global_ptr;

int main(){

	int a = 1;
	int b = 2;
	int c = 3;

	global_ptr = &a;

	if(a == 1){
		
		if(b == 1){

			b = 300;
			f1();
			f3();
			c = 100;
		}
		else {

			b = 300;
			f1();
			c = 200;
		}

	}

	else {

		c = 300;
		f3();
		c = 300;
	}

}

void f2(){

	int a = 2;
	int b = 2;

	global_ptr = &a;
	
	if(a==b ){

		if(b ==3){
				
			a = 1;
		}

		b = 2;

	}else{

		a = 1;
	}

}

void f1(){

	static int recur = 1;

	global_ptr = &recur;
	
	recur++;
	f2();
	recur++;
}

void f3(){

	
	int x = 1;
	int y = 2;
	int z = 3;
	
	global_ptr = &x;

	if(x == 1){

		f1();
		z = 1000;
	}

	else {

		if(y == 1){
			
			f1();
			z = 2000;
		}
		else {

			f1();
			z = 3000;
		}
	}
}

