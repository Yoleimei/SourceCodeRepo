#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define  MAX_EVENTS  5
#define  BUF_SIZE  256
#define  SOCK_PATH  ("test_sock")

int main()
{
	int epfd;
	struct epoll_event evlist[MAX_EVENTS];
	
	struct sockaddr_un addr;
	int sfd;
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
	
	epfd = epoll_create(1);
	if (0 > epfd) {
		printf("epoll_create error\n");
		return -1;
	}
	
	struct epoll_event sev;
	sev.events = EPOLLIN | EPOLLET;
	sev.data.fd = sfd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &sev) < 0) {
		printf("epoll_ctl error: %s\n", strerror(errno));
		return -1;
	}
	
	while (true) {
		int ret = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
		if (0 > ret) {
			if (EINTR == errno)
				continue;
			else {
				printf("epoll_wait error: %s\n", strerror(errno));
				return -1;
			}
		}
		
		for (int i = 0; i < ret; ++i) {
			if (evlist[i].data.fd == sfd) {
				int cfd = accept(sfd, NULL, NULL);
				if (0 > cfd) {
					printf("accept error: %s\n", strerror(errno));
					return -1;
				}
				
				struct epoll_event cev;
				cev.events = EPOLLIN | EPOLLET;
				cev.data.fd = cfd;
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &cev) < 0) {
					printf("epoll_ctl error: %s\n", strerror(errno));
					return -1;
				}
			} else {
				if (evlist[i].events & EPOLLIN) {
					read(evlist[i].data.fd, buf, BUF_SIZE);
					printf("read from client: %s\n", buf);
				}
			}
		}
	}
}