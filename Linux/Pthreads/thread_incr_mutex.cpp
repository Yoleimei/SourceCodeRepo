#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static int iGlobal_mtx = 0;
static int iGlobal_nonmtx = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void * threadFunc_mtx(void *arg)
{
	int iLocal;
	
	for (int i = 0; i < 65536; i++) {
		pthread_mutex_lock(&mtx);
		iLocal = iGlobal_mtx;
		iLocal++;
		iGlobal_mtx = iLocal;
		pthread_mutex_unlock(&mtx);
	}
	
	return NULL;
}

void * threadFunc_nonmtx(void *arg)
{
	int iLocal;
	
	for (int i = 0; i < 65536; i++) {
		iLocal = iGlobal_nonmtx;
		iLocal++;
		iGlobal_nonmtx = iLocal;
	}
	
	return NULL;
}

int main()
{
	pthread_t pid1, pid2, pid3, pid4;
	
	if (pthread_create(&pid1, NULL, threadFunc_mtx, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	if (pthread_create(&pid2, NULL, threadFunc_mtx, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	if (pthread_create(&pid3, NULL, threadFunc_nonmtx, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	if (pthread_create(&pid4, NULL, threadFunc_nonmtx, NULL) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
	pthread_join(pid3, NULL);
	pthread_join(pid4, NULL);
	
	printf("iGlobal_mtx = %d\n", iGlobal_mtx);
	printf("iGlobal_nonmtx = %d\n", iGlobal_nonmtx);
}