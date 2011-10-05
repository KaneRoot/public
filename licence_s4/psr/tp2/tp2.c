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
void crible_eratosthene(int n)
{
	int t[2], tprec[2],i;
	for(i = 0 ; i < n ; i++)
	{
		pipe(t);
		if(fork())
		{

			printf("FILS\n");
			return;
		}
	}
}
void copie(int a, int b)
{
	int n;
	char * c = malloc(sizeof(char) * 1);
	while((n = read(a,c,1)))
		write(b,c,n);
}
int main(int argc, char * argv[])
{
	//premier_exercice();
	//matproc(2, 3);
	//max_valeur_tube();
	
	return EXIT_SUCCESS;
}
