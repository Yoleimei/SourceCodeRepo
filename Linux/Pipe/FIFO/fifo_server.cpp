#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define  BUF_SIZE  16
#define  FIFO_PATH  ("test_fifo")

int main()
{
	int sfd;
	char buf[BUF_SIZE];
	
	unlink(FIFO_PATH);
	if (mkfifo(FIFO_PATH, 0777) < 0) {
		printf("mkfifo error: %s\n", strerror(errno));
		return -1;
	}
	
	sfd = open(FIFO_PATH, O_RDONLY);
	if (0 > sfd) {
		printf("open error: %s\n", strerror(errno));
		return -1;
	}
	
	while (true) {
		if (read(sfd, buf, BUF_SIZE) <= 0) {
			printf("read error: %s\n", strerror(errno));
			close(sfd);
			return -1;
		}
		printf("read from fifo: %s\n", buf);
	}
}