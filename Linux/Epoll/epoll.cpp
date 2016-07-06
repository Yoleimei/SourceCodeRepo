#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>

#define  MAX_EVENTS  5

int main()
{
	int epfd, ready, fd, s, j, numOpenFds;
	struct epoll_event ev;
	struct epoll_event evlist[MAX_EVENTS];
	
	char buf[512];
	
	epfd = epoll_create(1);
	if (0 > epfd) {
		printf("epoll_create error\n");
		return -1;
	}
	
	fd = open("text", O_RDONLY);
	if (0 > fd) {
		printf("open error\n");
		return -1;
	}
	
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
		printf("epoll_ctl error: %s\n", strerror(errno));
		return -1;
	}
	
	numOpenFds = 1;
	
	while (0 < numOpenFds) {
		ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
		if ( 0 > ready) {
			if (EINTR == errno)
				continue;
			else {
				printf("epoll_wait error\n");
				return -1;
			}
		}
		
		if (evlist[0].events & EPOLLOUT) {
			s = read(evlist[0].data.fd, buf, 512);
			printf("read: %s", buf);
		} else if (evlist[0].events & (EPOLLHUP | EPOLLERR)) {
			close(evlist[0].data.fd);
			numOpenFds--;
		}
	}
}