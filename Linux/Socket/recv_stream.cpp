#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <errno.h>

#define PATH ("/home/yuliming/Test/Socket/test.socket")
#define QUIT_STR ("quit")

void *foo(void *arg)
{
	int fd = *(int *)arg;
	int cnt = 0;
	char recv_buf[64] = "";
	while (cnt = read(fd, recv_buf, sizeof(recv_buf))) {
		printf("Recv: %s\n", recv_buf);
		if (0 == strncmp(recv_buf, QUIT_STR, sizeof(QUIT_STR))) {
			printf("sub thread exit");
			break;
		}
	}
}

int main()
{
	int sockfd = 0;
	struct sockaddr_un un;
	unlink(PATH);
	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, PATH, sizeof(PATH));

	unsigned int len = strlen(un.sun_path) + sizeof(un.sun_family);
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return -1;
	}

	if (bind(sockfd, (struct sockaddr *)&un, len) < 0) {
		close(sockfd);
		return -1;
	}
	printf("Bind is ok\n");

	int ret = listen(sockfd, 5);
	if (ret < 0) {
		printf("listen fail: %s\n", strerror(errno));
		return -1;
	}

	struct sockaddr_un un_client;
	socklen_t un_client_len = sizeof(un_client);
	memset(&un_client, 0, sizeof(un_client));

	int clientfd = 0;
	while ((clientfd = accept(sockfd, (struct sockaddr *)&un_client, &un_client_len)) > 0) {
		pthread_t pid;
		pthread_create(&pid, NULL, foo, (void *)&clientfd);
		pthread_detach(pid);
	}

	return 0;
}
