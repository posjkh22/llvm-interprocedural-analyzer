
int gv = 1;


void f1(){
	gv = 1;
}

void f2(){
	int a = 5;
	gv = a;
}

void f3(){
	static int b = 6;
	gv = b;
}

int main(){

	int a = 0;
	int b = 1;
	if( a == 0){
		f1();
	}else{

		if(b == 1){
			f2();
		}
		else{
			f3();
		}
	}

	return 0;
}
