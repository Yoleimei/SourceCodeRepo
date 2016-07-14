#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

void displayInotifyEvent(struct inotify_event *ev)
{
	printf("wd = %2d, cookie = %4d, mask = %d\n", ev->wd, ev->cookie, ev->mask);
	if (ev->mask & IN_OPEN) printf("IN_OPEN\n");
	if (ev->mask & IN_MODIFY) printf("IN_MODIFY\n");
	if (ev->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE\n");
}

int main()
{
	int inotifyFd, wd;
	char buf[1024];
	ssize_t cnt;
	char *p;
	struct inotify_event *event;
	
	inotifyFd = inotify_init();
	if (inotifyFd < 0) {
		printf("inotify_init error: %s\n", strerror(errno));
		return -1;
	}
	
	wd = inotify_add_watch(inotifyFd, "test.txt", IN_ALL_EVENTS);
	if (wd < 0) {
		printf("inotify_add_watch error: %s\n", strerror(errno));
		return -1;
	}
	
	while (true) {
		cnt = read(inotifyFd, buf, 1024);
		for (p = buf; p < buf + cnt; ) {
			event = (struct inotify_event *)p;
			displayInotifyEvent(event);
			p += sizeof(struct inotify_event) + event->len;
		}
	}
}
