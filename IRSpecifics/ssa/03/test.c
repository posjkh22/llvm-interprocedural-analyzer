
int main(){

	int addr_a = 1;
	int addr_b = 2;
	int addr_c = 4;
	int top_x = 3;
	int top_x2 = 5;
	int *top_z = &addr_b;
	int *top_y;
	int *top_w;

	addr_a = addr_b;
	top_x = addr_b; 

	top_w = &addr_c;

	if(*top_w == 10){

		*top_z = addr_c;
		addr_a++;
	}else{
		
		*top_z = addr_c;
	}


	top_y = &addr_a;
	*top_y += *top_z;
	*top_y += top_x;

	return 0;
}
