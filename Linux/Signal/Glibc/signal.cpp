#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string.h>

sigset_t oldset;
bool flag = true;

void sig_usr(int signum) 
{
	printf("receive signal: %s\n", strsignal(signum)); 
	
	if (SIGUSR2 == signum) {
		sigprocmask(SIG_SETMASK, &oldset, NULL);
		flag = false;
	}
}

void check_waiting_signal(const sigset_t *set, int signum)
{
	printf("%s is waiting: %d\n", strsignal(signum), sigismember(set, signum));
}

int main()
{
	struct sigaction sa;
	sigset_t sigset, pendingset;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_usr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigprocmask(SIG_BLOCK, &sigset, &oldset);
	
	sleep(5);  // only kill signal during sleep() time shall we get pending mask!
	sigemptyset(&pendingset);
	if (sigpending(&pendingset) < 0)
		printf("sigpending error\n");
	check_waiting_signal(&pendingset, SIGUSR1);
	check_waiting_signal(&pendingset, SIGUSR2);
	
	printf("wait for SIGUSR2\n");
	while (flag)
		sleep(1);
	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR2);
	printf("to do sigsuspend, SIGUSR2 is blocked\n");
#if 0
	// sigsuspend means doing the following code atomicly
	sigset_t prevset;
	sigprocmask(SIG_BLOCK, &sigset, &prevset);
	pause();
	sigprocmask(SIG_BLOCK, &prevset, NULL);
#endif
	if (sigsuspend(&sigset) < 0)  // sigsuspend will always return -1, and set errno to EINTR
		printf("sigsuspend error: %s\n", strerror(errno));
	printf("sigsuspend over\n");
	
	while (true)
		sleep(1);
}
