#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <sys/wait.h>

int temp;
void exo2_hand_int(int s)
{
	if(temp == 3)
	{
		printf("Pour quitter, entrez à nouveau Ctrl+C dans moins de 3 secondes\n");
		temp = 0;
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}
void exo2_hand_alarm(int s)
{
	if(temp != 3)
		temp++;
}
void exo2()
{
	sigset_t signaux;
	struct sigaction action;
	sigemptyset(&signaux);

	action.sa_handler = exo2_hand_int;
	sigaction(SIGINT,&action,NULL);
	action.sa_handler = exo2_hand_alarm;
	sigaction(SIGALRM,&action,NULL);

	while(1)
	{
		alarm(1);
		if(fork() == 0)
		{
			char * tmp[] = { "date", NULL };
			execve("date", tmp, NULL);
			exit(1); // execve ne s'est pas bien exécuté
		}
		else
			wait(NULL); // le père attend la fin d'exécution de son fils
	}
}
int main(int argc, char * argv[])
{
	temp = 3;
	exo2();
	return EXIT_SUCCESS;
}

