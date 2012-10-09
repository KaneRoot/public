#include <stdlib.h>     
#include <stdio.h>     

#define N 4
#define M 1000


typedef struct cell {
	struct cell * suivant;
	int        valeurs[N];
} Cellule;


Cellule * allocation()
{
	Cellule * tmp = malloc(sizeof(Cellule*));
	return tmp;
}

int longueur(Cellule * liste)
{
	if (liste==NULL)
		return 0;
	else
		return (1+longueur(liste->suivant));
}


int main()
{
	Cellule * maliste=allocation();
	Cellule * copie=maliste;
	int i, j;

	for(i=0; i<M; i++){
		maliste->suivant=allocation();
		maliste=maliste->suivant;
		for(j=0; j<N; j++)
			maliste->valeurs[j] = random();
	}

	printf(" %d\n", longueur(copie));
	return 0;
}
