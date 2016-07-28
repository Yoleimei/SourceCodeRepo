#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void error_exit(const char *str, bool flag)
{
	printf("%s error: %s\n", str, strerror(errno));
	
	if (flag)
		exit(-1);
}

int main()
{
	int fd, fd1, fd2;
	fd2 = 50;
	
	fd = open("test.txt", O_RDWR | O_TRUNC, 0660);
	
	fd1 = dup(fd);
	write(fd1, "Hello ", 6);
	close(fd1);
	
	if (dup2(fd, fd2) < 0)
		error_exit("dup2", true);
	if (close(fd) < 0)
		error_exit("close(fd)", true);
	write(fd2, "world!", 6);
	close(fd2);
}
