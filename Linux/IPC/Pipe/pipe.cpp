#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define  BUF_SIZE  16
#define  STR  ("Hello world!")

int main() 
{
	int pfd[2]; // [0]-read, [1]-write
	char buf[BUF_SIZE];
	ssize_t num;
	
	if (pipe(pfd) < 0) {
		printf("pipe error: %s\n", strerror(errno));
		return -1;
	}
	
	switch (fork()) {
		case -1:
			printf("fork error: %s\n", strerror(errno));
			return -1;
			break;
		case 0: // child
			close(pfd[1]);
			if ((num = read(pfd[0], buf, BUF_SIZE)) <= 0) {
				printf("read error: %s\n", strerror(errno));
				return -1;
			}
			
			printf("read from pipe: %s\n", buf);
			
			close(pfd[0]);
			
			break;
		default: // parent
			close(pfd[0]);
			write(pfd[1], STR, sizeof(STR));
			close(pfd[1]);
			break;
	}
}