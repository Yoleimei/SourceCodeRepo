#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define  SOCK_PATH  ("test_sock")

int main()
{
	struct sockaddr_un addr;
	int cfd;
	ssize_t numWrite;
	
	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (0 > cfd) {
		printf("socket error:%s\n", strerror(errno));
		return -1;
	}
	
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (connect(cfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
		printf("connect error:%s\n", strerror(errno));
		return -1;
	}
	
	numWrite = write(cfd, "Hello world!", sizeof("Hello world!"));
		
	close(cfd);
}