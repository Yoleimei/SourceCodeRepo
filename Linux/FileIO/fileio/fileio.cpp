#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define  BUF_SIZE  16

char* str_h_w = ("Hello World!");
char* str_y   = ("Yoleimei!");

void error_exit(const char* str)
{
	printf("%s error: %s\n", str, strerror(errno));
	exit(-1);
}

int main()
{
	int fd = -1;
	int dirfd = -1;
	char buf[BUF_SIZE] = { 0 };
	char buff[2][BUF_SIZE] = { 0 };
#if 0
	if (remove("text.txt") < 0)
		error_exit("remove");
#endif
	// basic file creat write read close
//	umask(0);
	if ((fd = open("text.txt", O_RDWR | O_TRUNC)) < 0 )
		error_exit("open");
	write(fd, str_h_w, strlen(str_h_w));
	fsync(fd);
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, BUF_SIZE - 1);
	printf("%s\n", buf);
	
	// pwrite pread
	pwrite(fd, str_y, strlen(str_y), 6);
	fsync(fd);
	pread(fd, buf, BUF_SIZE - 1, 0);
	printf("%s\n", buf);
	
	close(fd);
	
	// open openat 
	if ((dirfd = open(".", O_DIRECTORY)) < 0)
		error_exit("open");
	if ((fd = openat(dirfd, "text.txt", O_RDWR)) < 0)
		error_exit("openat");
	struct iovec iov1[2];
	iov1[0].iov_base = str_h_w;
	iov1[0].iov_len = strlen(str_h_w);
	iov1[1].iov_base = str_y;
	iov1[1].iov_len = strlen(str_y);
	
	// pwritev preadv
	pwritev(fd, iov1, sizeof(iov1)/sizeof(struct iovec), 0);
	fsync(fd);
	struct iovec iov2[2];
	iov2[0].iov_base = buff[0];
	iov2[0].iov_len = BUF_SIZE - 1;
	iov2[1].iov_base = buff[1];
	iov2[1].iov_len = BUF_SIZE - 1;
	preadv(fd, iov2, sizeof(iov2)/sizeof(struct iovec), 0);
	printf("%s\n", buff[0]);
	printf("%s\n", buff[1]);
	
	close(fd);
	close(dirfd);
}
