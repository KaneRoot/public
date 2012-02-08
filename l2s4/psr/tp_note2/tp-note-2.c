#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// EXERCICE 3 NON FINI
int nombre1,nombre2; // comptent l'endroit où on se situe sur les chaînes
int fichier;
void exo3_hand_P1(int s)
{
	char tmp[] = "abcdefghijklmnopqrstuvwxyz";
	if(nombre1 > strlen(tmp))
		exit(EXIT_SUCCESS);
	else
	{
		char c = tmp[nombre1];
		write(fichier,c,1);
		nombre1++;
	}
}
void exo3_hand_P2(int s)
{
	char tmp[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if(nombre2 > strlen(tmp))
		exit(EXIT_SUCCESS);
	else
	{
		char c = tmp[nombre2];
		write(fichier,c,1);
		nombre2++;
	}
}
void exo3()
{
	sigset_t signaux;
	struct sigaction action;
	sigemptyset(&signaux);

	// P1
	if(fork() == 0)
	{
		action.sa_handler = exo3_hand_P1;
		sigaction(SIGUSR1,&action,NULL);
		sigsuspend(&signaux);
	}
	// P2
	if(fork() == 0)
	{
		action.sa_handler = exo3_hand_P2;
		sigaction(SIGUSR1,&action,NULL);
		while(1)
		{
			sigsuspend(&signaux);
		}
	}

	wait(NULL);
	wait(NULL);

}
int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		printf("Usage : executable nomfichier\n");
		exit(EXIT_FAILURE);
	}
	nombre1 = 0;
	nombre2 = 0;
	fichier = open(argv[1],O_CREAT | O_WRONLY);
	exo3();
	return EXIT_SUCCESS;
}

