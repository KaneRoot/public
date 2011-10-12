#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			exit(0);
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
				exit(0);
			}
			wait(&status);
			exit(0);
		}
		wait(&status);
		exit(0);
	}
	wait(&status);
}
void ex1_famille_proc3()
{

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

