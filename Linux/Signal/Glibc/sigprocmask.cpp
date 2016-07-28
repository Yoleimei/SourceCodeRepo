#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

sigset_t oldmask;

void sig_usr(int signum) 
{
	printf("receive signal: %s\n", strsignal(signum)); 
	
	if (SIGUSR2 == signum)
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

int main()
{
	struct sigaction sa;
	sigset_t newmask;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_usr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	
	while (true)
		sleep(1);
}
