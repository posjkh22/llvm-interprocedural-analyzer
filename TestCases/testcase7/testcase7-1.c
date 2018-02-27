
#include <pthread.h>

void f1();
void f2();
void f3();

void f1(){
	f2();
}
void f2(){
	f3();
}
void f3(){
	int a = 1;
}


void task1(void *ptr){
	f1();
}

void task2(void *ptr){
	f2();
}


int main(){

	int status;
	int thread_id1;
	int thread_id2;	

	pthread_t thread[2];
	
	thread_id1 = pthread_create(&thread[0], NULL, task1, NULL);
	thread_id2 = pthread_create(&thread[1], NULL, task1, NULL);

	pthread_join(thread[0], &status);
	pthread_join(thread[1], &status);


	return 0;
}

