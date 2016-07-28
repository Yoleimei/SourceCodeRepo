#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#define PATH "/home/yuliming/Test/Socket/test.socket"

int main()
{
	int sockfd = 0;
	struct sockaddr_un un;
	memset(&un, 0, sizeof(un));

	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, PATH, sizeof(PATH));

	sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket error");
		return -1;
	}

	while (true) {
		static int counter = 0;
		char send_buf[64] = "";
		// sprintf(send_buf, "Counter is %d", counter);
		fgets(send_buf, 63, stdin);
		int len = strlen(un.sun_path) + sizeof(un.sun_family);
		sendto(sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&un, len);
		printf("Send: %s\n", send_buf);
		// sleep(1);
	}
}
