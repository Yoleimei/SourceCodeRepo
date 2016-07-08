#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define  BUF_SIZE  16
#define  STR  ("Hello world!")
#define  FIFO_PATH  ("test_fifo")

int main()
{
	int cfd;
	
	cfd = open(FIFO_PATH, O_WRONLY);
	if (0 > cfd) {
		printf("open error: %s\n", strerror(errno));
		return -1;
	}
	
	if (write(cfd, STR, sizeof(STR)) <= 0) {
		printf("write error: %s\n", strerror(errno));
		close(cfd);
		return -1;
	}
}