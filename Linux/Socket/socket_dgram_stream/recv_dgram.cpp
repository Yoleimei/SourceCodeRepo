#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PATH ("/home/yuliming/Test/Socket/test.socket")

int main()
{
	int sockfd = 0;
	struct sockaddr_un un;
	unlink(PATH);
	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, PATH, sizeof(PATH));

	unsigned int len = strlen(un.sun_path) + sizeof(un.sun_family);
	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		return -1;
	}

	if (bind(sockfd, (struct sockaddr *)&un, len) < 0) {
		close(sockfd);
		return -1;
	}
	printf("Bind is ok\n");

	while (true) {
		char recv_buf[64] = "";
		recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&un, &len);
		printf("Recv: %s\n", recv_buf);
	}

	return 0;
}
