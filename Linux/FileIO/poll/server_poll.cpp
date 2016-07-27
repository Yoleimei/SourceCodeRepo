#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/poll.h>
#include <errno.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define  BUF_SIZE    64
#define  PORT        6789
#define  MAX_CLIENT  512

int servfd = 0;
struct pollfd pfd[MAX_CLIENT];
	
void error_exit(const char *str, bool flag)
{
	printf("%s error: %s\n", str, strerror(errno));
	
	if (servfd > 0)
		close(servfd);
	
	if (flag)
		exit(-1);
}

int main()
{
	struct sockaddr_in servaddr;
	char buf[BUF_SIZE] = { 0 };
	int max_index = 0;
	
	for (int i = 0; i < MAX_CLIENT; i++) {
		pfd[i].fd = -1;
	}

	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_exit("socket", true);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		close(servfd);
		error_exit("bind", true);
	}

	if (listen(servfd, MAX_CLIENT) < 0) {
		close(servfd);
		error_exit("listen", true);
	}

	pfd[0].fd = servfd;
	pfd[0].events = POLLIN;
	max_index = 1;
	
	while (true) {
		int readyfds = 0;
		printf("start selecting\n");
		if ((readyfds = poll(pfd, max_index, -1)) < 0) {
			close(servfd);
			error_exit("select", true);
		}
		printf("select over, %d selected\n", readyfds);
		
		if (pfd[0].revents & POLLIN != 0) {
			struct sockaddr_in clieaddr;
			socklen_t addrlen = sizeof(clieaddr);
			char str_addr_src[32] = {0};
			char str_addr_dst[32] = {0};
			
			int clientfd = accept(servfd, (struct sockaddr *)&clieaddr, &addrlen);
			uint32_t s_addr = clieaddr.sin_addr.s_addr;
			sprintf(str_addr_src, "%u", s_addr);
			inet_ntop(AF_INET, str_addr_src, str_addr_dst, 31);
			printf("%s connected\n", str_addr_dst);
			
			int i = 0;
			for (i = 0; i < MAX_CLIENT; i++) {
				if (-1 == pfd[i].fd) {
					pfd[i].fd = clientfd;
					pfd[i].events = POLLIN;
					max_index = ((i+1) > max_index) ? (i+1) : max_index;
					break;
				}
			}
			if (MAX_CLIENT == i)
				error_exit("too many clients", true);
			
			if (--readyfds <= 0)
				continue;
		}
		
		for (int i = 0; i < max_index; i++)  {
			if (pfd[i].fd < 0)
				continue;
			if (pfd[i].revents & POLLIN != 0) {
				memset(buf, 0, BUF_SIZE);
				int iRet = read(pfd[i].fd, buf, BUF_SIZE);
				if (0 == iRet) {
					close(pfd[i].fd);
					pfd[i].fd = -1;
				}
				else
					printf("Recv: %s", buf);
			}
		}
	}
}
