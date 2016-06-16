#include <stdio.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd1 = open("text.txt", O_RDONLY);
	struct pollfd pfd[1] = {0};
    pfd[0].fd = fd1;
	pfd[0].events = POLLIN;

	int ret = poll(pfd, 1, -1);
    if (pfd[0].revents & POLLIN != 0) {
		char str[50] = "";
		read(fd1, str, 20);
		printf("%s", str);
	}
	close(fd1);
}
