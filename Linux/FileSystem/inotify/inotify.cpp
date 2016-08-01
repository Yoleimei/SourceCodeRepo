#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <poll.h>

/**
// Supported events suitable for MASK parameter of INOTIFY_ADD_WATCH.  
#define IN_ACCESS        0x00000001                          // File was accessed.  
#define IN_MODIFY        0x00000002                          // File was modified. 
#define IN_ATTRIB        0x00000004                          // Metadata changed.  
#define IN_CLOSE_WRITE   0x00000008                          // Writtable file was closed.  
#define IN_CLOSE_NOWRITE 0x00000010                          // Unwrittable file closed.  
#define IN_CLOSE         (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE) // Close.  
#define IN_OPEN          0x00000020                          // File was opened.  
#define IN_MOVED_FROM    0x00000040                          // File was moved from X.  
#define IN_MOVED_TO      0x00000080                          // File was moved to Y.  
#define IN_MOVE          (IN_MOVED_FROM | IN_MOVED_TO)       // Moves.  
#define IN_CREATE        0x00000100                          // Subfile was created.  
#define IN_DELETE        0x00000200                          // Subfile was deleted.  
#define IN_DELETE_SELF   0x00000400                          // Self was deleted.  
#define IN_MOVE_SELF     0x00000800                          // Self was moved.  

// Events sent by the kernel.  
#define IN_UNMOUNT       0x00002000                          // Backing fs was unmounted.  
#define IN_Q_OVERFLOW    0x00004000                          // Event queued overflowed.  
#define IN_IGNORED       0x00008000                          // File was ignored.  

// Helper events.  
#define IN_CLOSE         (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE) // Close.  
#define IN_MOVE          (IN_MOVED_FROM | IN_MOVED_TO)       // Moves.  

// Special flags.  
#define IN_ONLYDIR       0x01000000                          // Only watch the path if it is a directory.  
#define IN_DONT_FOLLOW   0x02000000                          // Do not follow a sym link.  
#define IN_EXCL_UNLINK   0x04000000                          // Exclude events on unlinked objects.  
#define IN_MASK_ADD      0x20000000                          // Add to the mask of an already existing watch.  
#define IN_ISDIR         0x40000000                          // Event occurred against dir.  
#define IN_ONESHOT       0x80000000                          // Only send event once.  
 */

void displayInotifyEvent(const char *fd_name, struct inotify_event *ev)
{
	printf("%s: wd = %2d, cookie = %4d, mask = %d   ", fd_name, ev->wd, ev->cookie, ev->mask);
	if (ev->mask & IN_ACCESS) printf("IN_ACCESS  ");
	if (ev->mask & IN_MODIFY) printf("IN_MODIFY  ");
	if (ev->mask & IN_CLOSE) printf("IN_CLOSE  ");
	if (ev->mask & IN_OPEN) printf("IN_OPEN  ");
	if (ev->mask & IN_CREATE) printf("IN_CREATE  ");
	if (ev->mask & IN_DELETE) printf("IN_DELETE  ");
	if (ev->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF  ");
	printf("\n");
}

int main()
{
	int notifyfd1, notifyfd2, wd1, wd2;
	struct pollfd pfd[2];
	char buf[1024];
	ssize_t cnt;
	char *p;
	struct inotify_event *event;
	
	notifyfd1 = inotify_init();
	if (notifyfd1 < 0) {
		perror("inotify_init error");
		return -1;
	}
	notifyfd2 = inotify_init();
	if (notifyfd2 < 0) {
		perror("inotify_init error");
		return -1;
	}
	
	wd1 = inotify_add_watch(notifyfd1, ".", IN_ALL_EVENTS);
	if (wd1 < 0) {
		perror("inotify_add_watch error\n");
		return -1;
	}
	wd2 = inotify_add_watch(notifyfd2, "test.txt", IN_ALL_EVENTS);
	if (wd2 < 0) {
		perror("inotify_add_watch error");
		return -1;
	}
	
	pfd[0].fd = notifyfd1;
	pfd[0].events = POLLIN;
	pfd[1].fd = notifyfd2;
	pfd[1].events = POLLIN;
	
	while (true) {
		printf("start polling\n");
		poll(pfd, 2, -1);
		printf("polling over\n");
		if (pfd[0].revents & POLLIN != 0) {
			cnt = read(pfd[0].fd, buf, 1024);
			for (p = buf; p < buf + cnt; ) {
				event = (struct inotify_event *)p;
				displayInotifyEvent(".", event);
				p += sizeof(struct inotify_event) + event->len;
			}
		}
		if (pfd[1].revents & POLLIN != 0) {
			cnt = read(pfd[1].fd, buf, 1024);
			for (p = buf; p < buf + cnt; ) {
				event = (struct inotify_event *)p;
				displayInotifyEvent("./test.txt", event);
				p += sizeof(struct inotify_event) + event->len;
			}
		}
	}
}
