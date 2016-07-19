#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define  MAX_NUM  200
#define  MIN_NUM  0

static int iGlobal = 100;
static pthread_mutex_t mtx       = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_plus  = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_minus = PTHREAD_COND_INITIALIZER;

void * threadFunc_plus(void *arg)
{
	int iLocal;
	int val;
	
	for (int i = 0; i < 10; i++) {
		sleep(1);
		pthread_mutex_lock(&mtx);
		
		val = rand() % 100;
		while (iGlobal + val > MAX_NUM) {
			printf("plus wait\n");
			pthread_cond_wait(&cond_plus, &mtx);
		}
		
		iLocal = iGlobal + val;
		printf("%3d + %3d = %3d\n", iGlobal, val, iLocal);
		iGlobal = iLocal;
		
		pthread_cond_signal(&cond_minus);
		pthread_mutex_unlock(&mtx);
	}
	
	return NULL;
}

void * threadFunc_minus(void *arg)
{
	int iLocal;
	int val;
	
	for (int i = 0; i < 10; i++) {
		sleep(1);
		pthread_mutex_lock(&mtx);
		
		val = rand() % 100;
		while (iGlobal - val < MIN_NUM) {
			printf("minus wait\n");
			pthread_cond_wait(&cond_minus, &mtx);
		}
		
		iLocal = iGlobal - val;
		printf("%3d - %3d = %3d\n", iGlobal, val, iLocal);
		iGlobal = iLocal;
		
		pthread_cond_signal(&cond_plus);
		pthread_mutex_unlock(&mtx);
	}
	
	return NULL;
}

int main()
{
	pthread_t pid1, pid2;
	
	srand((unsigned int)time(NULL));
	
	if (pthread_create(&pid1, NULL, threadFunc_plus, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	if (pthread_create(&pid2, NULL, threadFunc_minus, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
}