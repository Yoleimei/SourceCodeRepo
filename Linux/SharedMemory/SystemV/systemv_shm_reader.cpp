#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "binary_sems.h"

#define  SHM_KEY  0x1234
#define  SEM_KEY  0x5678

#define  SEM_WR  0
#define  SEM_RD  1

#define  BUF_SIZE  16

struct shmseg {
	int cnt;
	char buf[BUF_SIZE];
};

int main()
{
	int semid, shmid, xfrs, bytes;
	struct shmseg *shmp;
	
	semid = semget(SEM_KEY, 0, 0);
	if (semid < 0) {
		printf("semget error: %s\n", strerror(errno));
		return -1;
	}
	
	shmid = shmget(SHM_KEY, 0, 0);
	if (shmid < 0) {
		printf("shmid error: %s\n", strerror(errno));
		return -1;
	}
	
	shmp = (struct shmseg *)shmat(shmid, NULL, SHM_RDONLY);
	if ((void *)(-1) == shmp) {
		printf("shmat error: %s\n", strerror(errno));
		return -1;
	}
	
	for (xfrs = 0, bytes = 0; ; xfrs++) {
		if (reserveSem(semid, SEM_RD) < 0) {
			printf("reserveSem error: %s\n", strerror(errno));
			return -1;
		}
		
		if (1 == shmp->cnt)
			break;
		bytes += shmp->cnt;
		
		if (write(STDOUT_FILENO, shmp->buf, shmp->cnt) != shmp->cnt) {
			printf("write error: %s\n", strerror(errno));
		}
		
		if (releaseSem(semid, SEM_WR) < 0) {
			printf("reserveSem error: %s\n", strerror(errno));
			return -1;
		}
	}
	
	if (shmdt(shmp) < 0) {
		printf("shmdt error: %s\n", strerror(errno));
		return -1;
	}
	
	if (releaseSem(semid, SEM_WR) < 0) {
		printf("releaseSem error: %s\n", strerror(errno));
		return -1;
	}
	
	fprintf(stderr, "Received %d bytes (%d xfrs)\n", bytes, xfrs);
}