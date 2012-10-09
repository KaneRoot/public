#include <stdlib.h>     
#include <stdio.h>     


typedef struct cell {
	int           valeur;
	struct cell * suivant;
} Cellule;


Cellule * cons(Cellule * liste, int valeur)
{
	Cellule * new_cell = malloc(sizeof(Cellule));
	new_cell->valeur  = valeur;
	new_cell->suivant = liste;
	return new_cell;
}

Cellule * concat(Cellule * premiere, Cellule * deuxieme)
{
	Cellule * parcourt = premiere;

	if(parcourt==NULL) return deuxieme;
	while(parcourt->suivant!=NULL)
		parcourt = parcourt->suivant;

	parcourt->suivant = deuxieme;

	return premiere;
}

int longueur(Cellule * liste)
{
	if (liste==NULL || liste->suivant == liste)
		return 0;
	else
		return (1+longueur(liste->suivant));
}


int main()
{
	Cellule * liste1=NULL, * liste2=NULL,  * liste3=NULL,  * liste4=NULL;

	liste1=cons(liste1,1);
	liste2=cons(liste2,1);
	liste2=cons(liste2,1);
	liste3=cons(liste3,1);
	liste3=cons(liste3,1);
	liste3=cons(liste3,1);
	liste4=cons(liste4,1);
	liste4=cons(liste4,1);
	liste4=cons(liste4,1);
	liste4=cons(liste4,1);
	printf("Longueur liste1 = %d\n", longueur(liste1));
	printf("Longueur liste2 = %d\n", longueur(liste2));
	liste3=concat(liste2, liste1);
	printf("Longueur liste3 = %d\n", longueur(liste3));
	liste4=concat(liste3, liste1);
	printf("Longueur liste4 = %d\n", longueur(liste4));

	return 0;
}
