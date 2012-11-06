#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quitter(char * error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int allocation(int taille, int ** tableau)
{
	*tableau = malloc(sizeof(int) * taille);
	if( *tableau == NULL)
		return -1;
	return 0;
}
int comparaison_pg(int a, int b) { return a > b ; }
int comparaison_pp(int a, int b) { return a < b ; }

int main(int argc, char * argv[])
{
	int i = 0;
	int taille = 10;
	int * tableau = NULL;
	int (*p_comparaison)(int,int);

	p_comparaison = comparaison_pg;
	printf("%d \n", (*p_comparaison)(5,4));
	printf("%d \n", (*p_comparaison)(5,6));

	if( allocation(taille, &tableau) < 0)
		quitter("erreur");

	for(i = 0 ; i < taille ; i++)
		tableau[i] = i%(taille/2);
	for(i = 0 ; i < taille ; i++)
		printf("%d ", tableau[i]);
	printf("\n");

	
	return EXIT_SUCCESS;
}
