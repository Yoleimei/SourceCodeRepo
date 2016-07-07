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

union semun{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *array;  
};

int main()
{
	int semid, shmid, bytes, xfrs;
	struct shmseg *shmp;
	union semun dummy;
	
	semid = semget(SEM_KEY, 2, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (0 > semid) {
		printf("semget error: %s\n", strerror(errno));
		return -1;
	}
	if (initSemAvailable(semid, SEM_WR) < 0) {
		printf("initSemAvailable error: %s\n", strerror(errno));
		return -1;
	}
	if (initSemInUse(semid, SEM_RD) < 0) {
		printf("initSemInUse error: %s\n", strerror(errno));
		return -1;
	}
	
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (0 > shmid) {
		printf("shmget error: %s\n", strerror(errno));
		return -1;
	}
	shmp = (struct shmseg *)shmat(shmid, NULL, 0);
	if ((void *)(-1) == shmp) {
		printf("shmat error: %s\n", strerror(errno));
		return -1;
	}
	
	for (xfrs = 0, bytes = 0; ; xfrs++, bytes += shmp->cnt) {
		if (reserveSem(semid, SEM_WR) < 0) {
			printf("reserveSem error: %s\n", strerror(errno));
			return -1;
		}
		
		shmp->cnt = read(STDIN_FILENO, shmp->buf, BUF_SIZE);
		if (shmp->cnt < 0) {
			printf("read error: %s\n", strerror(errno));
		}
		
		if (releaseSem(semid, SEM_RD) < 0) {
			printf("releaseSem error: %s\n", strerror(errno));
			return -1;
		}
		
		if (1 == shmp->cnt)
			break;
	}
	
	if (reserveSem(semid, SEM_WR) < 0) {
		printf("reserveSem error: %s\n", strerror(errno));
		return -1;
	}
	
	if (semctl(semid, 0, IPC_RMID, dummy) < 0) {
		printf("semctl error: %s\n", strerror(errno));
		return -1;
	}
	if (shmdt(shmp) < 0) {
		printf("shmdt error: %s\n", strerror(errno));
		return -1;
	}
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("semctl error: %s\n", strerror(errno));
		return -1;
	}
	
	fprintf(stderr, "Sent %d bytes (%d xfrs)\n", bytes, xfrs);
}