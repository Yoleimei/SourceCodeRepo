#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define  MQ_NAME  ("/yoleimei_mq")

int main()
{
	char mq_str[512];
	mqd_t mqd;
	struct mq_attr attr;
	
	mqd = mq_open(MQ_NAME, O_RDONLY);
	if (mqd < 0) {
		printf("mq_open error: %s\n", strerror(errno));
		return -1;
	}
	
	if (mq_getattr(mqd, &attr) < 0) {
		printf("mq_getattr error: %s\n", strerror(errno));
		return -1;
	}
	
	if (mq_receive(mqd, mq_str, attr.mq_msgsize, 0) < 0) {
		printf("mq_send error: %s\n", strerror(errno));
		return -1;
	}
	
	printf("mq_recv: %s\n", mq_str);
	
	mq_unlink(MQ_NAME);
}