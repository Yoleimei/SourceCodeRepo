#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define PATH "/home/yuliming/Test/Socket/test.socket"

int main()
{
	int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un un;
	memset(&un, 0, sizeof(un));

	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, PATH, sizeof(PATH));

	int ret = connect(sockfd, (struct sockaddr *)&un, sizeof(un));
	if (ret < 0) {
		printf("socket error:%s\n", strerror(errno));
		return -1;
	}

	while (true) {
		static int counter = 0;
		char send_buf[64] = "";
		fgets(send_buf, 63, stdin);
		int len = strlen(un.sun_path) + sizeof(un.sun_family);
		write(sockfd, send_buf, sizeof(send_buf));
		printf("Send: %s\n", send_buf);
	}
}
