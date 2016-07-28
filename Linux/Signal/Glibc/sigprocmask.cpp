#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

sigset_t oldset;

void sig_usr(int signum) 
{
	printf("receive signal: %s\n", strsignal(signum)); 
	
	if (SIGUSR2 == signum)
		sigprocmask(SIG_SETMASK, &oldset, NULL);
}

void check_waiting_signal(const sigset_t *set, int signum)
{
	printf("%s is waiting: %d\n", strsignal(signum), sigismember(set, signum));
}

int main()
{
	struct sigaction sa;
	sigset_t newset, pendingset;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_usr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	sigemptyset(&newset);
	sigaddset(&newset, SIGUSR1);
	sigprocmask(SIG_BLOCK, &newset, &oldset);
	
	sleep(5);  // only kill signal during sleep() time shall we get pending mask!
	sigemptyset(&pendingset);
	if (sigpending(&pendingset) < 0)
		printf("sigpending error\n");
	check_waiting_signal(&pendingset, SIGUSR1);
	check_waiting_signal(&pendingset, SIGUSR2);
	
	while (true)
		sleep(1);
}
