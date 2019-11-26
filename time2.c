#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "timefunction.h"
#define MILLION 1000000

int main(){

	struct timeval tpstart, tpend;
	long timediff;

	int thr_id, status;
	int data = 1;
	pthread_t p_thread[2];

	gettimeofday(&tpstart, NULL);

	thr_id = pthread_create(&p_thread[0], NULL, matrix, (void*)&data);
	thr_id = pthread_create(&p_thread[1], NULL, matrix, (void*)&data);

	pthread_join(p_thread[0], (void*)&status);
	pthread_join(p_thread[1], (void*)&status);
	
	gettimeofday(&tpend, NULL);

	timediff = MILLION * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;

	printf("It took %ld msec \n", timediff);

}	
