#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define  SHM_KEY   0x2345
#define  SHM_SIZE  32
#define  SEM_KEY   0x4567
#define  SEM_NUM   0
#define  TIMES     65536

union semun {  
    int val;  
    struct semid_ds *buf;  
    unsigned short *array;  
};

int main()
{
	pid_t pid;
	if ((pid = fork()) > 0) {
		// shared memory
		int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if (shmid < 0) {
			printf("parent process open shm fail\n");
			return 0;
		}
		int *shmp = reinterpret_cast<int *>(shmat(shmid, NULL, 0));
		if ((void *)(-1) == shmp) {
			printf("parent process shmat error\n");
			return 0;
		}
		memset(shmp, 0, SHM_SIZE);
		
		// semaphore
		int semid = semget(SEM_KEY, 2, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if (semid < 0) {
			printf("parent process semget error: %s\n", strerror(errno));
			return 0;
		}
		
		union semun arg;
		arg.val = 1;
		semctl(semid, SEM_NUM, SETVAL, arg);
		
		sleep(1);
		struct sembuf sops;
		for (int i = 0; i < TIMES; i++) {
			sops.sem_num = SEM_NUM;
			sops.sem_op = -1;
			sops.sem_flg = 0;
			while (semop(semid, &sops, 1) < 0) {
				if (errno != EINTR)
					return -1;
			}
			
			(*shmp)++;
			//printf("++: %d\n", *shmp);
			
			sops.sem_num = SEM_NUM;
			sops.sem_op = 1;
			sops.sem_flg = 0;
			semop(semid, &sops, 1);
		}
		
		sleep(3);
		printf("int: %d\n", *shmp);
		union semun dummy;
		semctl(semid, 0, IPC_RMID, dummy);
		shmdt(shmp);
		shmctl(shmid, IPC_RMID, 0);
	}
	else if(0 == pid) {
		sleep(1);
		// shared memory
		int shmid = shmget(SHM_KEY, 0, 0);
		if (shmid < 0) {
			printf("child process open shm fail\n");
			return 0;
		}
		int *shmp = reinterpret_cast<int *>(shmat(shmid, NULL, 0));
		if ((void *)(-1) == shmp) {
			printf("child process shmat error\n");
			return 0;
		}
		
		// semaphore
		int semid = semget(SEM_KEY, 0, 0);
		if (semid < 0) {
			printf("child process semget error: %s\n", strerror(errno));
			return -1;
		}
		
		struct sembuf sops;
		for (int i = 0; i < TIMES; i++) {
			sops.sem_num = SEM_NUM;
			sops.sem_op = -1;
			sops.sem_flg = 0;
			while (semop(semid, &sops, 1) < 0) {
				if (errno != EINTR)
					return -1;
			}
			
			(*shmp)--;
			//printf("--: %d\n", *shmp);
			
			sops.sem_num = SEM_NUM;
			sops.sem_op = 1;
			sops.sem_flg = 0;
			semop(semid, &sops, 1);
		}
		
		sleep(2);
		shmdt(shmp);
	}
}
