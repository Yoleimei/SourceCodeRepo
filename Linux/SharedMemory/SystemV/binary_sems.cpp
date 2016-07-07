#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>

union semun{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *array;  
};

bool bsUseSemUndo = false;
bool bsRetryOnEintr = true;

int initSemAvailable(int semid, int semnum)
{
	union semun arg;
	
	arg.val = 1;
	return semctl(semid, semnum, SETVAL, arg);
}

int initSemInUse(int semid, int semnum)
{
	union semun arg;
	
	arg.val = 0;
	return semctl(semid, semnum, SETVAL, arg);
}

int reserveSem(int semid, int semnum)
{
	struct sembuf sops;
	
	sops.sem_num = semnum;
	sops.sem_op = -1;
	sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;
	
	while (semop(semid, &sops, 1) < 0) {
		if (errno != EINTR || !bsRetryOnEintr)
			return -1;
	}
	return 0;
}

int releaseSem(int semid, int semnum)
{
	struct sembuf sops;
	
	sops.sem_num = semnum;
	sops.sem_op = 1;
	sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;
	
	return semop(semid, &sops, 1);
}
