#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main()
{
	struct stat st;
	
	if (stat("readme.txt", &st) < 0) {
		printf("stat error: %s", strerror(errno));
		return -1;
	}
	
	printf("File type:                ");
	switch (st.st_mode & S_IFMT) {
	case S_IFREG:  printf("regular file\n");      break;
	case S_IFDIR:  printf("directory\n");         break;
	case S_IFCHR:  printf("character device\n");  break;
	case S_IFBLK:  printf("block device\n");      break;
	case S_IFLNK:  printf("symbolic link\n");     break;
	case S_IFIFO:  printf("FIFO or pipe\n");      break;
	case S_IFSOCK: printf("socket\n");            break;
	default:       printf("unknown file\n");      break;
	}
	printf("Device containing i-node: major=%ld, minor=%ld\n", (long)major(st.st_dev), (long)minor(st.st_dev));
	printf("I-node number:            %ld\n", (long)st.st_ino);
	printf("Mode:                     %lo\n", (unsigned long)st.st_mode);
	printf("Number of hard links:     %ld\n", (long)st.st_nlink);
	printf("Ownership:                UID=%ld, GID=%ld\n", (long)st.st_uid, (long)st.st_gid);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
		printf("Device number (st_rdev):  major:%ld, minor:%ld\n", (long)major(st.st_rdev), (long)minor(st.st_rdev));
	printf("File size:                %lld bytes\n", (long long)st.st_size);
	printf("Optimal I/O block size:   %ld bytes\n", (long)st.st_blksize);
	printf("512B blocks allocated:    %lld\n", (long long)st.st_blocks);
	printf("Last file access:         %s", ctime(&st.st_atime));
	printf("Last file modification:   %s", ctime(&st.st_mtime));
	printf("Last file change status:  %s", ctime(&st.st_ctime));
}