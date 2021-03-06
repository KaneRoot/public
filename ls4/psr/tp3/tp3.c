#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>

/* réponse exo 1 : on a une fonction hand_sigusr1, SIGUSR1 lance un appel à cette fonction,
 * le père crée un fils, affiche son propre PID, en même temps le fils affiche son PID,
 * et le père envoie à son fils le signal USR1 pour que son fils se termine, il attend son retour
 * et affiche sa valeur de retour
 */
#define INT_MAX 1e3
int n = 0;
int val_defaut = 0;
int u0;
int p[2];

//
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
	nb_alea1 = (rand() % 6)+1;
	nb_alea2 = (rand() % 6)+1;
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
void syracuse()
{
	
}
void exo5_pere_usr1(int s)
{
	int i, nb_alea = 0;
	srand(time(NULL));
	nb_alea = (rand() % 100); // Entre 0 et 100
	char buf[5];
	for(i = 0 ; i < 5 ; i++)
		buf[i] = '\0';
	
	snprintf(buf,5, "%d",nb_alea);
	write(p[1],buf, 5);
}
void exo5(int n)
{
	int i, *fils,pid;

	
	fils = malloc(sizeof(int) * n);
	// 1. Créer n fils
	for(i = 0 ; i < n ; i++)
	{
		if((pid = fork()) == 0)
		{ // dans le fils
			close(p[1]);
			sleep(1);
			printf("Fils numéro : %d PID : %d\n",i, getpid());
			exit(0);
		}
		else
		{
			fils[i] = pid;
		}
	}
	close(p[0]);

	for(i = 0 ; i < n ; i++)
	{
		printf(" fils[%d] : %d\n",i,fils[i]);
		wait(NULL);
	}

	printf("On a fini de lire la fin des fils\n");
}
int main(int argc, char * argv[])
{
	//int i;
	exo2(atoi(argv[1]));
	//exo3();
	//printf("%d \n",syracuse(10));
	/*for(i = 1 ; i < INT_MAX ; i++)
	{
		u0 = i;
		syracuse();
	}
	*/
	/*
	pipe(p);
	if(argc == 2)
		exo5(atoi(argv[1]));
	else
		printf("Usage : bla nb\n");
	*/
	return EXIT_SUCCESS;
}

