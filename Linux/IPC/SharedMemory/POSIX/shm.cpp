#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define  SHM_NAME  ("yoleimei.shm")

int main()
{
	pid_t pid;
	if ((pid = fork()) > 0) {
		int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			printf("parent process open shm fail\n");
			return 0;
		}
		ftruncate(fd, 4096);
		char *ptr = reinterpret_cast<char*>(mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		if (MAP_FAILED == ptr) {
			printf("parent process mmap error\n");
			return 0;
		}
		const char str[] = "Hello world!";
		strncpy(ptr, str, sizeof(str));
		printf("*ptr: %s\n", ptr);
		sleep(3);
		shm_unlink(SHM_NAME);
	}
	else if(0 == pid) {
		sleep(2);
		int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			printf("child process open shm fail\n");
			return 0;
		}
		ftruncate(fd, 4096);
		char *ptr = reinterpret_cast<char*>(mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		if (MAP_FAILED == ptr) {
			printf("child process mmap error\n");
			return 0;
		}
		char str[32];
		strncpy(str, ptr, 32);
		printf("%s\n", ptr);
		shm_unlink(SHM_NAME);
	}
}
