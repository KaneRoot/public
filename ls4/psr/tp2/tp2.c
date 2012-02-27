#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void premier_exercice()
{
	printf("Bonjour ");
	fflush(stdout);
	if(fork())
		printf("Monsieur\n");
	else
		printf("Madame\n");
}
void matproc(int n , int m)
{
	if(m == 0)
		return;

	int i;
	for(i = 0 ; i < n; i++)
	{
		if(fork() == 0)
		{
			printf("Processus %d \n", getpid());
			matproc(n, m - 1);
			exit(0);
		}
	}
	for(i = 0 ; i < n ; i++)
		wait(NULL);
}
void max_valeur_tube()
{
	int p[2];
	int somme = 0;
	char c[1];
	c[0] = 'A';
	pipe(p);
	while((write(p[1],c,1)))
		printf("Val max à rentrer dans le pipe %d\n",somme++);
}
void copie(int a, int b)
{
	int n;
	char c[1];
	while((n = read(a,c,1)))
		write(b,c,n);
}
// Pas fini
void crible_eratosthene(int n)
{
	int t[2], tprec[2],i,pid;
	for(i = 0 ; i < n ; i++)
	{
		pipe(t);
		if((pid =fork()))
		{
			if(i == 0)
			{
				close(1); close(t[0]);
				copie(0,t[1]);
				close(0); close(t[1]);
				exit(EXIT_SUCCESS);
			}
			else
			{
				close(t[0]); close(tprec[1]);
				copie(tprec[0],t[1]);
				close(tprec[0]); close(t[1]);
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			close(t[1]);
			tprec[0] = t[0];
		}
	}
	copie(t[0],1);
	close(t[0]);
	close(1);
	for(i = 0 ; i < n ; i++)
		wait(NULL);
}
int main(int argc, char * argv[])
{
	//premier_exercice();
	//matproc(2, 3);
	//max_valeur_tube();
	
	return EXIT_SUCCESS;
}
