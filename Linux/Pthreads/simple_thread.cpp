#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void * threadFunc(void *arg)
{
	char *s = (char *)arg;
	
	printf("child thread: %s\n", s);
	
	return (void *)strlen(s);
}

int main()
{
	pthread_t pid;
	char buf[] = "Hello world!";
	unsigned int len;
	char len_str[16];
	void *res = NULL;  
	
	if (pthread_create(&pid, NULL, threadFunc, (void *)buf) < 0) {
		printf("pthread_create error: %s\n", strerror(errno));
		return -1;
	}
	
	if (pthread_join(pid, &res) < 0) {
		printf("pthread_join error: %s\n", strerror(errno));
		return -1;
	}
	
	sprintf(len_str, "%p", res); 
	sscanf(len_str, "%x", &len);
	printf("main thread: child thread returned %u\n", len);
}