#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd = -1;
	char buf[32] = { 0 };
	
	fd = open ("test.txt", O_RDWR);
	memset(buf, 0, sizeof(buf));
	read(fd, buf, sizeof(buf));
	printf("%s\n", buf);
	
	if (ftruncate(fd, 8) < 0)
		printf("ftruncate error: %s\n", strerror(errno));
	memset(buf, 0, sizeof(buf));
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, sizeof(buf));
	printf("%s\n", buf);
	
	close(fd);
	
	if (truncate("test.txt", 4) < 0)
		printf("truncate error: %s\n", strerror(errno));
	fd = open ("test.txt", O_RDONLY);
	memset(buf, 0, sizeof(buf));
	read(fd, buf, sizeof(buf));
	printf("%s\n", buf);
	close(fd);
}
