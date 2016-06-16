#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	int fd[2];
	int w, r;
	char str[30] = "This is a test string";
	char buf[30] = "";
	pid_t pid;

	socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
	pid = fork();
	if (pid > 0) {
		printf("parent process's pid is %d\n", getpid());
		close(fd[1]); // close s[1] in main process
		write(fd[0], str, strlen(str));
	}
	else if (0 == pid) {
		printf("child process's pid is %d\n", getpid());
		close(fd[0]); // close s[0] in child process
	}
	else {
		printf("fork process error\n");
	}

	read(fd[1], buf, 30);
	printf("receive str: %s\n", buf);
}
