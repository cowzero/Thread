#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile int cnt = 100000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* cycle1(void* data){
 
	int i = 1000000;

	while(i != 0){
		pthread_mutex_lock(&mutex);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		cnt--;
		printf("cycle1 : %d\n", cnt);
		i--;
		
		pthread_mutex_unlock(&mutex);

		sleep(0.00001);
	}
}

void* cycle2(void* data){
	
	int i = 1000000;
	
	while(i != 0){
		pthread_mutex_lock(&mutex);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		cnt--;
		printf("cycle2 : %d\n", cnt);
		i--;

		pthread_mutex_unlock(&mutex);

		sleep(0.00001);
	}
}

int main(){

	int thr_id;
	pthread_t p_thread[4];
	int status;
	int data  = 1;

 	thr_id = pthread_create(&p_thread[0], NULL, cycle1, (void*)&data);
 	thr_id = pthread_create(&p_thread[1], NULL, cycle2, (void*)&data);
 	thr_id = pthread_create(&p_thread[2], NULL, cycle1, (void*)&data);
 	thr_id = pthread_create(&p_thread[3], NULL, cycle2, (void*)&data);

	pthread_join(p_thread[0], (void*)&status);
	pthread_join(p_thread[1], (void*)&status);
	pthread_join(p_thread[2], (void*)&status);
	pthread_join(p_thread[3], (void*)&status);

	status = pthread_mutex_destroy(&mutex);

	printf("code = %d\n", status);
	printf("programing is end\n");
	return 0;
}
