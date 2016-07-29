#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

/**
 * struct __dirstream {
 *     void *__fd;
 *     char *__data;
 *     int __entry_data;
 *     char *__ptr;
 *     int __entry_ptr;
 *     size_t __allocation;
 *     size_t __size;
 *     __libc_lock_define (, __lock)
 * };
 * typedef struct __dirstream DIR;
 */

/**
 * struct dirent {
 *     ino_t          d_ino;       // inode number 
 *     off_t          d_off;       // offset to the next dirent 
 *     unsigned short d_reclen;    // length of this record 
 *     unsigned char  d_type;      // type of file; not supported by all file system types 
 *     char           d_name[256]; // filename 
 * };
 */

int main()
{
	DIR *dirp = NULL;
	struct dirent *dp = NULL;
	
	dirp = opendir(".");
	printf("dirfd: %d\n", dirfd(dirp));
	while (true) {
		dp = readdir(dirp);
		if (NULL == dp) 
			break;
		printf("inode number:              %lu\n", dp->d_ino);
		printf("offset to the next dirent: %ld\n", dp->d_off);
		printf("length of this record:     %d\n",  dp->d_reclen);
		printf("type of file:              %d\n",  dp->d_type);
		printf("filename:                  %s\n",  dp->d_name);
	}
	closedir(dirp);
}
