#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>

#define  SHM_NAME  ("/yoleimei_shm")
#define  SEM_NAME  ("/yoleimei_sem")
#define  TIMES      65536

int main()
{
	pid_t pid;
	if ((pid = fork()) > 0) {
		// shared memory
		int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			printf("parent process open shm fail\n");
			return 0;
		}
		ftruncate(fd, 4096);
		int *p = reinterpret_cast<int*>(mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		if (MAP_FAILED == p) {
			printf("parent process mmap error\n");
			return 0;
		}
		*p = 0;
		
		// semaphore
		sem_t *pSem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
		
		sleep(1);
		for (int i = 0; i < TIMES; i++) {
			sem_wait(pSem);
			(*p)++;
			sem_post(pSem);
		}
		
		sleep(2);
		printf("int: %d\n", *p);
		sem_close(pSem);
		sem_unlink(SEM_NAME);
		munmap(reinterpret_cast<void*>(p), sizeof(int));
		shm_unlink(SHM_NAME);
	}
	else if(0 == pid) {
		sleep(1);
		// shared memory
		int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			printf("child process open shm fail\n");
			return 0;
		}
		ftruncate(fd, 4096);
		int *p = reinterpret_cast<int*>(mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		if (MAP_FAILED == p) {
			printf("child process mmap error\n");
			return 0;
		}
		
		// semaphore
		sem_t *pSem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
		
		for (int i = 0; i < TIMES; i++) {
			sem_wait(pSem);
			(*p)--;
			sem_post(pSem);
		}
		
		sleep(2);
		sem_close(pSem);
		sem_unlink(SEM_NAME);
		munmap(reinterpret_cast<void*>(p), sizeof(int));
		shm_unlink(SHM_NAME);
	}
}
