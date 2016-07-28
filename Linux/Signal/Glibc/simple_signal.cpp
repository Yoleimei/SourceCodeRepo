#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void sig_usr(int signum) 
{
	printf("receive signal: %s\n", strsignal(signum)); 
}

int main()
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_usr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	while (true)
		sleep(1);
}
