/**
 * ipcs -q: 查看消息队列
 */
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define  MAX_MTEXT  1024
#define  MSG_KEY    0x1234
#define  TYPE       100

struct mbuf {
	long mtype;
	char mtext[MAX_MTEXT];
};

int main()
{
	int msqid, msgLen;
	struct mbuf msg;
	
	msqid = msgget(MSG_KEY, 0660 | IPC_CREAT); // Permission denied
	if (msqid < 0) {
		printf("msgget error: %s\n", strerror(errno));
		return -1;
	}
	
	if (msgrcv(msqid, &msg, sizeof(msg), TYPE, 0) < 0) {
		printf("msgrcv error: %s\n", strerror(errno));
		return -1;
	}
	
	msgctl(msqid, IPC_RMID, 0);
	
	printf("msgrcv: %s\n", msg.mtext);
}