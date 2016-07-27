#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define  BUF_SIZE    64
#define  PORT        6789
#define  MAX_CLIENT  512

int servfd = 0;
	
void error_exit(const char *str, bool flag)
{
	printf("%s error: %s\n", str, strerror(errno));
	
	if (flag) {
		close(servfd);
		exit(-1);
	}
}

int main()
{
	int epfd = -1;
	struct sockaddr_in servaddr;
	char buf[BUF_SIZE] = { 0 };
	struct epoll_event ev;
	struct epoll_event evlist[MAX_CLIENT];

	if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_exit("socket", true);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		error_exit("bind", true);
	}

	if (listen(servfd, MAX_CLIENT) < 0) {
		error_exit("listen", true);
	}

	if ((epfd = epoll_create(1)) < 0) { // Since Linux 2.6.8, the size argument is ignored, but must be greater than zero
		error_exit("epoll_create", true);
	}
	ev.data.fd = servfd;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, servfd, &ev) < 0) {
		error_exit("epoll_ctl", true);
	}
	
	while (true) {
		int readyfds = 0;
		printf("start epolling\n");
		if ((readyfds = epoll_wait(epfd, evlist, MAX_CLIENT, -1)) < 0) {
			error_exit("epoll", true);
		}
		printf("epoll over, %d epolled\n", readyfds);
		
		for (int i = 0; i < readyfds; i++)  {
			if ((evlist[i].events & EPOLLERR) ||  
				(evlist[i].events & EPOLLHUP) ||  
				(!(evlist[i].events & EPOLLIN))) {
				error_exit("epoll", false);
				continue;
			}
			else if (evlist[i].data.fd == servfd) {
				struct sockaddr_in clieaddr;
				socklen_t addrlen = sizeof(clieaddr);
				char str_addr_src[32] = {0};
				char str_addr_dst[32] = {0};
				
				int clientfd = accept(servfd, (struct sockaddr *)&clieaddr, &addrlen);
				uint32_t s_addr = clieaddr.sin_addr.s_addr;
				sprintf(str_addr_src, "%u", s_addr);
				inet_ntop(AF_INET, str_addr_src, str_addr_dst, 31);
				printf("%s connected\n", str_addr_dst);
				
				ev.data.fd = clientfd;
				ev.events = EPOLLIN | EPOLLET;
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev) < 0) {
					error_exit("epoll_ctl", true);
				}
			}
			else if(evlist[i].events & EPOLLIN != 0) {
				memset(buf, 0, BUF_SIZE);
				int iRet = read(evlist[i].data.fd, buf, BUF_SIZE);
				if (0 == iRet) {
					close(evlist[i].data.fd);
					ev.data.fd = evlist[i].data.fd;
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_DEL, evlist[i].data.fd, &ev);
				}
				else
					printf("Recv: %s", buf);
			}
		}
	}
}
