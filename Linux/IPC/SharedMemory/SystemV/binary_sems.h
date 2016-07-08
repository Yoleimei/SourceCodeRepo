extern bool bsUseSemUndo;
extern bool bsRetryOnEintr;

int initSemAvailable(int semid, int semnum); 
int initSemInUse(int semid, int semnum); 
int reserveSem(int semid, int semnum); 
int releaseSem(int semid, int semnum); 
