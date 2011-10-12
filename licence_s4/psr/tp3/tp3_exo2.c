#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

// Pour cet exercice, tout est dans le main
int main(int argc, char * argv[])
{
	int palpha[2],pdigit[2],nb_chiffres = 0, nb_lettres = 0;
	char c;
	char buf[1];
	int status; // pour la fin des fils

	// premier fils, alpha
	pipe(palpha);
	if(fork() == 0)
	{
		close(0); 
		close(palpha[1]);
		while((read(palpha[0],buf,1)))
		{
			nb_lettres++;
		}
		printf("nb de lettres = %d\n", nb_lettres);
		exit(EXIT_SUCCESS);
	}
	close(palpha[0]); // ne nous sert plus

	// second fils, digit
	pipe(pdigit);
	if(fork() == 0)
	{
		close(0); 
		close(palpha[1]);
		close(pdigit[1]);
		while((read(pdigit[0],buf,1)))
		{
			nb_chiffres++;
		}
		printf("nb de chiffres = %d\n", nb_chiffres);
		exit(EXIT_SUCCESS);
	}
	while((c = getchar()) != EOF)
	{
		buf[0] = c;
		if(isalpha(c)) write(palpha[1],buf,1);
		if(isdigit(c)) write(pdigit[1],buf,1);
	}
	close(palpha[1]);
	close(pdigit[1]);

	// On attend la fin des fils
	wait(&status);
	wait(&status);
	return EXIT_SUCCESS;
}

