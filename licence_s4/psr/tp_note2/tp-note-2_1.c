#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>

int combinaison;
void exo1_hand_int(int s)
{
	if(combinaison == 0)
		combinaison++;
	else if(combinaison == 2)
		combinaison++;
	else
		combinaison = 0;
	
}
void exo1_hand_tstp(int s)
{
	if(combinaison == 1)
		combinaison++;
	else if(combinaison == 3)
		exit(EXIT_SUCCESS);
	else
		combinaison = 0;
}
void exo1()
{
	sigset_t signaux;
	struct sigaction action;
	sigemptyset(&signaux);

	action.sa_handler = exo1_hand_int;
	sigaction(SIGINT,&action,NULL);
	action.sa_handler = exo1_hand_tstp;
	sigaction(SIGTSTP,&action,NULL);

	while(1)
		sigsuspend(&signaux);
}
int main(int argc, char * argv[])
{
	combinaison = 0;
	exo1();
	return EXIT_SUCCESS;
}

