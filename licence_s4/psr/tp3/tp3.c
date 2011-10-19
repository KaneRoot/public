#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* réponse exo 1 : on a une fonction hand_sigusr1, SIGUSR1 lance un appel à cette fonction,
 * le père crée un fils, affiche son propre PID, en même temps le fils affiche son PID,
 * et le père envoie à son fils le signal USR1 pour que son fils se termine, il attend son retour
 * et affiche sa valeur de retour
 */
int n = 0;
int val_defaut = 0;
void hand_exo2(int s)
{
	printf("\n");
	n = val_defaut;
}
void hand_exo2_alrm(int s)
{
	printf("%d ",n);
	n--;
	fflush(stdout);
}
void exo2(int nval)
{
	struct sigaction action;
	sigset_t signaux;
	sigemptyset(&signaux);
	n = nval;
	val_defaut = n;
	action.sa_handler = hand_exo2;
	sigaction(SIGINT,&action,NULL);
	action.sa_handler = hand_exo2_alrm;
	sigaction(SIGALRM,&action,NULL);
	while(n >= 0)
	{
		alarm(1);
		sigsuspend(&signaux);
	}
	printf("\n Alerte !!!!!!!!\n");
}
void hand_exo3_int(int s)
{
	n--;
	int nb_alea1 = 0;
	int nb_alea2 = 0;
	srand(time(NULL));
	nb_alea1 = rand() % 7;
	nb_alea2 = rand() % 7;
	printf("%d %d\n",nb_alea1,nb_alea2);
	if(n <= 0)
		exit(EXIT_SUCCESS);
}
void hand_exo3_alrm(int s)
{
	n = 2;
}
void exo3()
{
	struct sigaction action;
	sigset_t signaux;
	sigemptyset(&signaux);
	n = 2;
	action.sa_handler = hand_exo3_int;
	sigaction(SIGINT,&action,NULL);
	action.sa_handler = hand_exo3_alrm;
	sigaction(SIGALRM,&action,NULL);
	while(1)
	{
		alarm(1);
		sigsuspend(&signaux);
	}
}
int main(int argc, char * argv[])
{
	//exo2(atoi(argv[1]));
	exo3();
	
	return EXIT_SUCCESS;
}

