#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_usr(int) 
{
	printf("receive user signal\n");
}

int main()
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR\n");

	sleep(1000);
}
