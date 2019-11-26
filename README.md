# Thread
1. 개요
pthread 라이브러리 또는 자바 스레드로 여러 스레드가 하나의 전역변수에 동시에 접근해서 충돌이 발생하는 문제를 재현하고 mutex 또는 synchronized를 사용하여 이 문제를 해결한다. 

2. 프로그램 구조 설명
 
 2.1 함수에 관한 설명

-void* cycle1(void* data)
: 전역변수를 사용해 반복문 안에서 전역변수를 25번씩 감소시키는 함수. 

-void* cycle2(void* data)
: 전역변수를 사용해 반복문 안에서 전역변수를 25번씩 감소시키는 함수. 

-int pthread_mutex_lock(pthread_mutex_t *mutex)
:뮤텍스 잠금 함수. 해당 뮤텍스에 대해서 잠금을 시도. 해당 뮤택스가 다른 쓰레드에 의해 이미 잠겨있다면 잠금을 얻을 때까지 봉쇄한다. 

-int pthread_mutex_unlock(pthread_mutex_t *mutex)
:뮤텍스 잠금 해제 함수. 해당 영역에서의 작업을 마친 후 잠금을 해제한다.

-int pthread_mutex_destroy(pthread_mutex_t *mutex)
:뮤텍스 자원을 제거하는 함수, 성공할 경우 0을 반환하고 실패한 경우 에러코드를 반환한다.

-int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void), void *arg)
:쓰레드 생성 함수. 매개변수는 차례대로 쓰레드 식별자, 쓰레드 특성(기본 설정일 경우 NULL), 수행할 함수 이름, 함수의 매개변수 이다. 성공한 경우 0을 반환한다. 

-int pthread_join(pthread_t th, void**thread_return)
:쓰레드 조인 함수. 식별번호 th로 시작된 thread가 종료되는 것을 기다림. 매개변수는 차례대로 쓰레드 식별자, 쓰레드의 리턴 값(NULL이 아닌 경우, pointer로 쓰레드의 리턴값을 받아올 수 있다.)이다. 성공한 경우 0을 반환하고 실패한 경우 잘못된 식별 번호나 detach상태를 반환한다.











2.2 다이어그램




3. 실행 결과
-Makefile


global.c를 먼저 컴파일한 후에 쓰레드를 컴파일 하기 위해서 –lpthread를 더 추가했다.
global.o를 링킹하여 hw1 실행파일을 만들었다.

-오류 발생

·
· (과정이 너무 길어 중간 과정은 생략하였다.)
·

cnt 초기값이 10000000, 쓰레드가 총 4개, 반복문이 1000000번, 각 반복문마다 cnt—를 25번씩 수행하므로 마지막 cnt 값이 0 이어야 하는데 75가 나왔다. 이는 한 쓰레드가 값을 변경하기도 전에 다른 쓰레드가 그 값을 가져감으로써 일어난 일이라고 볼 수 있다. 

-문제 해결

·
· (과정이 너무 길어 중간 과정은 생략하였다.)
·

마지막 cnt의 값이 0이므로 올바른 결과가 나왔음을 알 수 있다.
크리티컬 섹션에서 동시간에 단지 하나의 쓰레드만 접근하도록 제한함으로써 문제를 해결할 수 있었다.
Mutex를 사용하여 cnt값을 읽어와서 연산을 한 후 결과를 저장하는 부분을 임계영역으로 지정함으로써 문제를 해결하였다.


4. 고찰
 처음에 교수님이 주신 예제를 참고해서 돌려보았는데 컴퓨터 사양이 딸려서 돌아가지 않았다. 이를 참고 좀 더 간단한 프로그램을 짜고자 했다.
 메이크 파일을 할 때 실행 파일명과 메이크 명령어를 같게 했는데 계속 오류가 떴다. 컴파일 명령어에는 아무리 봐도 문제가 없었는데 한 참을 해메다가 그 둘의 이름이 같으면 안된다는 사실을 알았다. 앞으로는 실행 파일명을 반드시 메이크 명령어와 다르게 해야겠다고 뼈저리게 느꼈다.
  쓰레드에서 수행할 함수를 만들 때 매개변수가 따로 필요가 없어서 매개변수가 없는 함수로 만들었다. 그런데 pthread_create() 함수를 사용할 때 이 함수의 매개변수 중에 사용할 함수의 매개변수를 필요로하는 것이 있었다. 없어도 문제가 되지 않을 것 같아서 컴파일을 해보았는데, 경고가 떴다. 그래서 매개변수가 따로 필요가 없지만 임의의 매개변수를 받도록 바꾸었다. 경고가 최대한 없도록 해야겠다고 생각했다.
 오류가 발생하도록 함수를 짤 때, 처음에 전역변수를 volatile이 아닌 그냥 int 로 선언하였다. voltaile 변수로 선언한다면 쓰레드 1이 volatile 변수에 쓰기 작업을 하고 쓰레드 2가 바로 직후에 같은 volatile 변수를 읽을 경우, volatile 변수를 쓰기 직전에 모든 변수를 쓰레드 1에서 볼 수 있고 쓰레드 2 또한 볼 수 있다는 사실을 알았다. 그렇다면 volatile로 선언한다면 더 오류가 잘 나지 않을까 싶어 voltaile로 선언하였다. 그러나 오류는 나지 않았다. 오류가 날 확률을 더 높이기 위해 원래는 반복문 속의 연산이 cnt--; 하나 뿐이었는데 연산을 더 복잡하게 한다면 한 쓰레드가 연산하는 시간이 길어져 결과를 도출해 내기도 전에 다른 쓰레드가 그 값을 가져갈 확률이 놓을 것 같아서 연산을 더 복잡하게 해 보았다. 그러나 이 또한 오류는 발생하지 않았다. 그래서 연산 횟수를 늘려 보았다. cnt— 의 횟수를 25번으로 늘렸지만 오류는 발생하지 않았다. 연산의 복잡함은 여기서 더 늘리지는 않고 반복문의 횟수를 점차 늘려보았다. 처음에는 100번 그다음에는 1000번 하다가 나중에는 1000000번까지 해보았다. 1000000번까지 하니 프로그램을 돌리는 시간이 너무 길어져서 처음에는 sleep(1)만 하였지만 시간을 확 줄여서 sleep(0.0001)로 바꿨다. 그래도 오류는 나지 않았다. 원래 쓰래드를 2개만 돌렸었지만 쓰래드를 4개로 늘렸다. (쓰레드를 5개 이상 돌리니까 컴퓨터 사양이 딸려서 돌아가지 않았다.) 마침내 오류가 발생하였다!!
 오류가 발생하는 것을 눈으로 보게 되니 쓰레드를 완전히 믿을 수 없게 됐다. mutex를 사용해 문제를 해결하였지만 mutex또한 복잡한 경우에 문제가 많고 운영체제가 앞으로 발전해야할 부분이 많다고 느꼈다. 
 
5. 프로그램 소스 파일

<global.c>

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile int cnt = 100000000;  //값이 깨지는 경우가 더 쉽게 발생하도록 하기 위해 voltile로 선언
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 생성

void* cycle1(void* data){

 	int i = 1000000; //오류가 잘 나도록 반복문을 최대한 많이 돌리기 위해 큰 숫자로 선언 

	while(i != 0){//전역변수를 사용하는 연산 수행

		pthread_mutex_lock(&mutex); //임계영역 시작, 뮤텍스 잠금

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
		
		pthread_mutex_unlock(&mutex); //임계영역 끝, 뮤텍스 잠금해제
		sleep(0.00001); //프로그램을 빠르게 돌리기 위해 아주 작은 시간 동안만 멈춘다
	}
}

void* cycle2(void* data){//cycle2와 이름만 다르고 하는 일은 같은 함수이다.

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
	pthread_t p_thread[4]; //쓰레드 4개 선언
	int status; //뮤텍스 제거 성공 여부를 저장할 변수
	int data  = 1; //함수에 넘길 매개변수 아무 숫자로 선언한다(pthread_create함수에서 매개변수가 없으면 경고가 뜨기 때문에 이를 해결하기 위해 매개변수가 있는 함수를 만들었고, 실제로 함수에서 그 매개변수를 사용하지 않았으므로 아무 숫자나 지정해도 상관 없다.

//쓰레드 4개 생성
 	thr_id = pthread_create(&p_thread[0], NULL, cycle1, (void*)&data); 
 	thr_id = pthread_create(&p_thread[1], NULL, cycle2, (void*)&data); 
 	thr_id = pthread_create(&p_thread[2], NULL, cycle1, (void*)&data); 
 	thr_id = pthread_create(&p_thread[3], NULL, cycle2, (void*)&data); 

//쓰레드 4개 조인
	pthread_join(p_thread[0], (void*)&status);
	pthread_join(p_thread[1], (void*)&status);
	pthread_join(p_thread[2], (void*)&status);
	pthread_join(p_thread[3], (void*)&status);

	status = pthread_mutex_destroy(&mutex); //더 이상 뮤텍스를 사용할 일이 없으므로 제거,
	printf("code = %d\n", status);
	printf("programing is end\n");
	return 0;
}

6. 자료 출처
http://m.egloos.zum.com/butcher18/v/1273149

1. 개요
행렬 곱셈을 수행하는 단일스레드와 멀티스레드 프로그램을 작성하여 수행 시간을 비교한다.

2. 프로그램 구조 설명

 2.1 함수에 관한 설명

-void* matrix(void* data)
: 행렬을 곱하는 함수. 2X2행렬 두 개를 임의의 수로 초기화한 후, 두 행렬을 곱한다.

-int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void), void *arg)
:쓰레드 생성 함수. 매개변수는 차례대로 쓰레드 식별자, 쓰레드 특성(기본 설정일 경우 NULL), 수행할 함수 이름, 함수의 매개변수 이다. 성공한 경우 0을 반환한다. 

-int pthread_join(pthread_t th, void**thread_return)
:쓰레드 조인 함수. 식별번호 th로 시작된 thread가 종료되는 것을 기다림. 매개변수는 차례대로 쓰레드 식별자, 쓰레드의 리턴 값(NULL이 아닌 경우, pointer로 쓰레드의 리턴값을 받아올 수 있다.)이다. 성공한 경우 0을 반환하고 실패한 경우 잘못된 식별 번호나 detach상태를 반환한다.

 2.2 다이어그램









3. 실행 결과
-makefile


time1.c를 먼저 컴파일한 후에 쓰레드를 컴파일 하기 위해서 –lpthread를 더 추가했다.
time1.o를 링킹하여 hw2_1 실행파일을 만들었다. 
마찬가지로 time2.c를 먼저 컴파일한 후에 쓰레드를 컴파일 하기 위해서 –lpthread를 더 추가했다.
time2.o를 링킹하여 hw2_2 실행파일을 만들었다.

-단일 쓰레드


프로그램을 돌릴 때마다 수행시간은 제각각이었지만 단일 쓰레드의 경우 일반적으로 약 100~1000 msec 정도 임을 알 수 있었다. 










-멀티 쓰레드


멀티 쓰레드의 경우도 마찬가지로 프로그램을 돌릴 때마다 제각각이었지만 일반적으로 약 1000 ~ 4000 msec임을 알 수 있었다. 단순한 프로그램의 경우에는 단일 쓰레드 보다 멀티쓰레드의 수행시간이 훨씬 길다는 것을 확인할 수 있었다.

4. 고찰
 행렬을 곱하는 함수를 만들 때 처음에는 사용자에게 입력받는 함수를 만들었다. 그러나 수행 시간을 측정할 때 입력하는 시간까지 포함해서 계산이 돼서 단일 쓰레드와 멀티 쓰레드의 수행 시간을 정확하게 비교하기가 애매했다. 그래서 임의로 행렬을 만든 후에 곱하는 함수로 바꿨다.
 난수를 생성하는 시간 차이 때문인지 매번 프로그램을 돌릴 때마다 시간이 달랐다. 그러나 프로그램이 단순할 경우 단일 쓰레드 보다 멀티 쓰레드일 때가 일반적으로 수행 시간이 더 길다는 것은 알 수 있었다. 2개의 쓰레드만 돌려서 확인해 보았지만 훨씬 더 많은 쓰레드를 돌릴 경우 확연한 차이를 볼 수 있을 것이다. 
 아주 간단한 프로그램만 돌려 보았는데 좀 더 복잡한 경우에는 시간 차이가 어떻게 나는 지 궁금해 졌다. 다음에 확인해 보아야겠다. 
 프로세스 여러개를 돌리는 것보다 멀티 쓰레드를 사용하는 쪽이 훨씬 더 간편하다고 느껴졌다. 앞으로 자원 공유가 필요한 경우 쓰레드를 더욱 애용해야 겠다.
 
5. 프로그램 소스 파일

<timeffunction.h>
void* matrix(void* data);

<timefunction.c>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* matrix(void* data){//행렬 곱셈 함수

	int i, j, k;
	static int a[2][2]; //2X2 행렬로 선언
	static int b[2][2]; //2X2행렬로 선언
	static int c[2][2]; //곱해진 결과 행렬. 2X2행렬로 선언
	
	srand((unsigned)time(NULL)); //매번 수행할 때마다 다른 값을 얻기 위함

	printf("\n----------- A ----------\n");

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			a[i][j] = rand() % 10 ; //a행렬을 0~10 사이 임의의 값으로 초기화 한다
		}
	} 
	for (i = 0 ; i < 2 ; i++){ //a행렬 값 출력
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", a[i][j]);
		}
		printf("\n");
	} 

	printf("\n----------- B ----------\n");

	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			b[i][j] = rand() % 10 ; //b행렬을 0~10 사이 임의의 값으로 초기화 한다
		}
	}
	for (i = 0 ; i < 2 ; i++){ //b행렬 값 출력
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", b[i][j]);
		}
		printf("\n");
	}

	printf("\n--------- A * B --------\n");
	
	for (i = 0 ; i < 2 ; i++){
		for (j = 0 ; j < 2 ; j++){
			 c[i][j] = 0; //c행렬 0으로 초기화
		}
	}
	for (i = 0 ; i < 2 ; i++){ //a*b
		for (j = 0 ; j < 2 ; j++){
			for (k = 0 ; k < 2 ; k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	for (i = 0 ; i < 2 ; i++){ //c행렬 값 출력
		for (j = 0 ; j < 2 ; j++){
			printf("%4d ", c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

<time.c> //단일 쓰레드 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "timefunction.h"
#define MILLION 1000000

int main(){
	struct timeval tpstart, tpend; //시작 시간, 끝나는 시간 선언
	long timediff; //시간 차이 = 수행 시간
	int thr_id, status; //쓰레드 식별자, 쓰레드 리턴값 
	int data = 1; //함수에 넘길 매개변수. 아무 숫자로 선언한다(pthread_create함수에서 매개변수가 없으면 경고가 뜨기 때문에 이를 해결하기 위해 매개변수가 있는 함수를 만들었고, 실제로 함수에서 그 매개변수를 사용하지 않았으므로 아무 숫자나 지정해도 상관 없다.
	pthread_t p_thread; //쓰레드 선언 

	gettimeofday(&tpstart, NULL); //시작 시간 측정

	thr_id = pthread_create(&p_thread, NULL, matrix, (void*)&data); //쓰레드 생성
	pthread_join(p_thread, (void*)&status); //쓰레드 조인

	gettimeofday(&tpend, NULL); //끝나는 시간 측정

	timediff = MILLION * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec – tpstart.tv_usec;
	//총 수행시간
	printf("It took %ld msec \n", timediff);
}


<time2.c> //멀티쓰레드
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "timefunction.h"
#define MILLION 1000000

Int main(){
	struct timeval tpstart, tpend; //시작 시간, 끝나는 시간 선언
	long timediff; //시간 차이 = 수행 시간
	int thr_id, status; //쓰레드 식별자, 쓰레드 리턴값 
	int data = 1; //함수에 넘길 매개변수. 아무 숫자로 선언한다(pthread_create함수에서 매개변수가 없으면 경고가 뜨기 때문에 이를 해결하기 위해 매개변수가 있는 함수를 만들었고, 실제로 함수에서 그 매개변수를 사용하지 않았으므로 아무 숫자나 지정해도 상관 없다.
	pthread_t p_thread[2]; //쓰레드 2개 선언

	gettimeofday(&tpstart, NULL); //시작 시간 측정

	thr_id = pthread_create(&p_thread[0], NULL, matrix, (void*)&data); //쓰레드 1 생성
	thr_id = pthread_create(&p_thread[1], NULL, matrix, (void*)&data); //쓰레드 2 생성
	pthread_join(p_thread[0], (void*)&status); //쓰레드 1 조인
	pthread_join(p_thread[1], (void*)&status); //쓰레드 2 조인
	
	gettimeofday(&tpend, NULL); //끝나는 시간

	timediff = MILLION * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
	//총 수행시간
	printf("It took %ld msec \n", timediff);
}	


6. 자료 출처
조교님 실행 예제, http://m.egloos.zum.com/butcher18/v/1273149 

