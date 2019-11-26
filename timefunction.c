#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* matrix(void* data){

	int i, j, k;

	static int a[2][2];
	static int b[2][2];
	static int c[2][2];

	srand((unsigned)time(NULL));


	printf("\n----------- A ----------\n");

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			a[i][j] = rand() % 10 ;
		}
	}
	
	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", a[i][j]);
		}
		printf("\n");
	}

	printf("\n----------- B ----------\n");

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			b[i][j] = rand() % 10 ;
		}
	}
	
	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", b[i][j]);
		}
		printf("\n");
	}
	
	printf("\n--------- A * B --------\n");

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			 c[i][j] = 0;
		}
	}

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			for (k = 0 ; k < 2 ; k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}

	}


	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", c[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
