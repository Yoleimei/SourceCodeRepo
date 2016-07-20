#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_usr(int) 
{
	printf("receive user signal\n");
}

int main()
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_usr;
	sigaction(SIGUSR1, &sa, NULL);

	sleep(1000);
}
