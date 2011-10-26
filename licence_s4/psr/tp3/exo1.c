#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <stdlib.h>
#include   <stdio.h>
#include   <sys/types.h>
#include   <unistd.h>
#include   <sys/wait.h>
#include   <signal.h>
struct sigaction action;
void hand_sigusr1(int sig)
{
	printf("(de %d) Signal SIGUSR1 recu\n", getpid());
	exit(0);
}
int main() 
{
	pid_t pid;
	int status;
	action.sa_handler=hand_sigusr1;
	sigaction(SIGUSR1,&action,NULL);
	if((pid=fork())==0)
	{
		printf("Je suis le fils de PID %d\n", getpid());
		/* processus fils bouclant */
		while(1) { };
	}
	printf("Je suis le pere de PID %d\n", getpid());
	if(kill(pid,0)==-1) // test d'existance
		printf("(de %d) Fils %d inexistant\n", getpid(), pid);
	else
	{
		printf("(de %d) Envoi du signal SIGUSR1 au processus %d\n", getpid (), pid);
		kill(pid,SIGUSR1);
	}
	pid=waitpid(pid,&status,0);
	printf("(de %d) Status du fils %d : %d\n",getpid(),pid,status);
	exit(EXIT_SUCCESS);
}
