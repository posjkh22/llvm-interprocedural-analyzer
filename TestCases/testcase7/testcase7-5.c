#include <stdlib.h>
#include <pthread.h>


void t2_fnc1(int *ptr1, int *ptr2){

	 free(ptr1);
	 free(ptr2);
}


void task1(void *ptr){

	int *ptr1 = (int *)malloc(sizeof(int));
	int *ptr2 = (int *)malloc(sizeof(int));

	int a  =0;
	if(a == 0){
		free(ptr1);

	}else{
		free(ptr1);
		free(ptr2);
	}
}

void task2(void *ptr){

	int *ptr1 = (int *)malloc(sizeof(int));
	int *ptr2 = (int *)malloc(sizeof(int));

	int a = 0;
	if( a == 0){

		free(ptr1);
		free(ptr2);
		free(ptr2);

	}else{
		
		t2_fnc1(ptr1, ptr2);

	}

	

}


int main(){

	int status;
	int thread_id1;
	int thread_id2;	

	pthread_t thread[2];
	
	thread_id1 = pthread_create(&thread[0], NULL, task1, NULL);
	thread_id2 = pthread_create(&thread[1], NULL, task2, NULL);

	pthread_join(thread[0], &status);
	pthread_join(thread[1], &status);


	return 0;
}

