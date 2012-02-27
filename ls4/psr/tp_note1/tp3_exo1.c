#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Les 3 manières de créer des processus sont dans des fonctions différentes
void ex1_famille_proc1()
{
	int i,status;
	for(i = 0; i < 3 ; i++)
	{
		if(fork() == 0)
		{
			printf("Je suis fils%d mon numero est le : %d, mon père est le : %d\n",
					i+1,
					getpid(),
					getppid());
			exit(EXIT_SUCCESS);
		}
	}
	for(i = 0; i < 3 ; i++)
		wait(&status);

}
void ex1_famille_proc2()
{
	int status;
	if(fork() == 0)
	{
		printf("Je suis fils1 mon numero est le : %d, mon père est le : %d\n",
				getpid(),
				getppid());
		if(fork() == 0)
		{
			printf("Je suis fils2 mon numero est le : %d, mon père est le : %d\n",
					getpid(),
					getppid());
			if(fork() == 0)
			{
				printf("Je suis fils3 mon numero est le : %d, mon père est le : %d\n",
						getpid(),
						getppid());
				exit(EXIT_SUCCESS);
			}
			wait(&status);
			exit(EXIT_SUCCESS);
		}
		wait(&status);
		exit(EXIT_SUCCESS);
	}
	wait(&status);
}
void ex1_famille_proc3()
{
	int i,status;
	for(i = 0 ; i < 2 ; i++)
	{
		// i == 0 : création du premier fils qui créera un second
		if(i == 0)
		{
			if(fork() == 0) // premier fils
			{
				printf("Je suis fils1 mon numero est le : %d, mon père est le : %d\n",
						getpid(),
						getppid());
				if(fork() == 0)
				{
					printf("Je suis fils2 mon numero est le : %d, mon père est le : %d\n",
							getpid(),
							getppid());
					exit(0); // fin du second fils
				}
				wait(&status);
				exit(EXIT_SUCCESS);
			}
		}
		else // création du fils 3
		{
			if(fork() == 0) // fils 3
			{
				printf("Je suis fils3 mon numero est le : %d, mon père est le : %d\n",
						getpid(),
						getppid());
				exit(EXIT_SUCCESS);
			}
		}
	}
	for(i = 0 ; i < 2 ; i++) // Attente de la fin des 2 fils
		wait(&status);
}

int main(int argc, char * argv[])
{
	printf("1)\n");
	ex1_famille_proc1();

	printf("2)\n");
	ex1_famille_proc2();

	printf("3)\n");
	ex1_famille_proc3();

	return EXIT_SUCCESS;
}

