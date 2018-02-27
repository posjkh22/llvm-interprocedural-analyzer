
typedef struct _t{

	int a;
	char b;

}STR;



STR func(){

	STR obj;
	obj.a = 1;
	obj.b = 'a';

	return obj;
}

STR *func2(STR *global_obj){

	global_obj->a = 2;
	global_obj->b = 'c';

	return global_obj;
}

int main(){

	STR a;
	STR *b;
	STR c;

	a = func();
	b = func2(&c);
	

	return 0;
}
