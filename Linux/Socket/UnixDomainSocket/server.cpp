#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define  BUF_SIZE  256
#define  SOCK_PATH  ("test_sock")

int main()
{
	struct sockaddr_un addr;
	int sfd, cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (0 > sfd) {
		printf("socket error:%s\n", strerror(errno));
		return -1;
	}
	
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
	unlink(SOCK_PATH);
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
		printf("bind error:%s\n", strerror(errno));
		return -1;
	}
	
	if (listen(sfd, 5) < 0) {
		printf("listen error:%s\n", strerror(errno));
		return -1;
	}
	
	while (true) {
		cfd = accept(sfd, NULL, NULL);
		if (0 > cfd) {
		printf("accept error:%s\n", strerror(errno));
		return -1;
		}
		
		while((numRead = read(cfd, buf, BUF_SIZE)) > 0) {
			printf("read from socket: %s\n", buf);
		}
		
		close(cfd);
	}
}