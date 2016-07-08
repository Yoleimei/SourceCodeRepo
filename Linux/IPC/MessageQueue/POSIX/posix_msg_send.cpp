#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define  MQ_NAME  ("/yoleimei_mq")

int main()
{
	char mq_str[] = "Hello world!";
	mqd_t mqd;
	
	mqd = mq_open(MQ_NAME, O_WRONLY); // need mount by superuser man(7) mq_overview
	if (mqd < 0) {
		printf("mq_open error: %s\n", strerror(errno));
		return -1;
	}
	
	if (mq_send(mqd, mq_str, sizeof(mq_str), 0) < 0) {
		printf("mq_send error: %s\n", strerror(errno));
		return -1;
	}
	
	mq_unlink(MQ_NAME);
}