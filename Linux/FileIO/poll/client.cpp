#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define  PORT      6789

void error_exit(const char *str, bool flag)
{
	printf("%s error: %s\n", str, strerror(errno));
	if (flag)
		exit(-1);
}

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		error_exit("connect", true);
	}
	printf("[client] connected\n");

	while (true) {
		char send_buf[64] = "";
		fgets(send_buf, 63, stdin);
		write(sockfd, send_buf, sizeof(send_buf));
		printf("Send: %s", send_buf);
	}
}
