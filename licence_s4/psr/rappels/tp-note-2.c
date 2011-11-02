#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define SLEEP 5

void traite(int s)
{
	printf("TRAITE :: signal %d\n",s);
}
void arret(int s)
{
	printf("ARRET :: signal %d\n",s);
	exit(EXIT_SUCCESS);
}
void kill_fils(int s)
{
	printf("ARRET FILS :: signal %d\n",s);
}
int main(int argc, char * argv[])
{
	int pid;
	if((pid = fork()) == 0 )
	{
		close(0);
		struct sigaction action, action2;
		sigset_t signaux;
		sigfillset(&signaux);
		sigdelset(&signaux, SIGUSR1);
		sigdelset(&signaux, SIGALRM);

		action.sa_handler = traite;
		action.sa_flags = 0;
		sigfillset(&action.sa_mask);

		sigaction(SIGALRM, &action, NULL);

		action2.sa_handler = arret;
		action2.sa_flags = 0;
		sigfillset(&action2.sa_mask);

		sigaction(SIGUSR1, &action2, NULL);

		while(1)
		{
			alarm(1);
			sigsuspend(&signaux);
		}
	}
	else
	{
		struct sigaction action;
		sigset_t signaux;
		sigfillset(&signaux);
		sigdelset(&signaux, SIGALRM);

		action.sa_handler = kill_fils;
		action.sa_flags = 0;
		sigaction(SIGALRM, &action, NULL);

		alarm(SLEEP+1);
		printf("Sleep %d\n", SLEEP);
		sigsuspend(&signaux);
		//sleep(SLEEP);
		kill(pid, SIGUSR1);
		wait(NULL);
	}
	return EXIT_SUCCESS;
}

