#include <stdlib.h>
#include <pthread.h>

int *t1_fnc1(int *ptr1){

	int *a = ptr1;
	return a;
}

int *t1_fnc2(int *ptr2, int *ptr3){

	return ptr2;
}

void t1_fnc3(int *ptr2, int *ptr3){

	int a = 0;
	free(ptr2);
	free(ptr3);

}

/////////////////////////////////////////////////


int *t2_fnc1(int *ptr1){

	int *a = ptr1;
	return a;
}

int *t2_fnc2(int *ptr2, int *ptr3){

	return ptr2;
}

void t2_fnc3(int *ptr2, int *ptr3){

	int a = 0;
	free(ptr2);
	free(ptr3);

}




void task1(void *ptr){
	
	int *ptr1;
	int *ptr2;
	int *ptr3;

	int a = 0;
	int b = 1;
	int c = 2;
	int *returnPtr;

	if( a == 0){
	
		ptr1 = (int *)malloc(sizeof(int));
		ptr2 = (int *)malloc(sizeof(int));
		ptr3 = (int *)malloc(sizeof(int));

		if(b == 0){

			/* Not free for ptr2, ptr3 */
			returnPtr = t1_fnc1(ptr1);
			free(returnPtr);
		}

		else{

			/* Double free for ptr3 */
			returnPtr = t1_fnc1(ptr1);
			free(returnPtr);
			t1_fnc3(ptr2, ptr3);
			free(ptr3);
		}

	}
	else{
		free(ptr1);
	}


}

void task2(void *ptr){

	int *ptr1 = (int *)malloc(sizeof(int));
	int *ptr2 = (int *)malloc(sizeof(int));
	int *ptr3 = (int *)malloc(sizeof(int));

	int *returnPtr;

	returnPtr = t2_fnc1(ptr1);
	free(returnPtr);
	
	returnPtr = t2_fnc2(ptr2, ptr3);
	
	t2_fnc3(returnPtr, ptr3);
	

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

