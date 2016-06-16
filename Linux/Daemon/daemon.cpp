#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>

int main()
{
	pid_t pid;
	int i, fd;
	char buf[] = "This is a daemon... ";
	char buff[64] = " ";
	char time_str[32] = "";
	pid = fork(); // 01. create process
	if (pid < 0) {
		printf("fork error\n");
	}
	else if (pid > 0) {
		exit(0);
	}
	else
		;

	setsid(); // 02. create new session
	chdir("/"); // change current dir to root
	umask(0); // set file author mask
	for (i = 0; i < getdtablesize(); ++i) {
		close(i); // close file descriptor
	}

	while (true) {
		if (fd = open("/tmp/test_daemon.log", O_CREAT | O_WRONLY | O_APPEND, 0600) < 0) {
			printf("open file error\n");
			exit(1);	
		}
		time_t time_now = time(NULL);
		sprintf(time_str, "%s", ctime(&time_now));
		// memset(time_str, 0, sizeof(time_str));
		// strcpy(time_str, ctime(time(NULL)));
		memset(buff, 0, sizeof(buff));
		strncpy(buff, buf, sizeof(buf));
		strncat(buff, time_str, sizeof(time_str));
		// strncat(buff, "\n", 1);
		write(fd, buff, sizeof(buff));
		close(fd);
		sleep(10);
	}
}
