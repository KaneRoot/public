#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"
#include "ABPO0.h"

void afficher_arbre(Abp a)
{
	int i;
	for(i = 0 ; i < n(a) ; i++)
		printf("v(a,%d) = %f\n",i,v(a,i));
}

void ajout_suppression_echange()
{
	printf("\033[31mTest : ajout_suppression_echange\033[00m\n");
	int i;
	Abp a = lambda();
	printf("Ajout de 6 valeurs à un arbre a\n");
	for(i = 0 ; i < 6 ; i++)
		inser(a,i);
	afficher_arbre(a);
	printf("Suppression de 2 éléments dans l'arbre a\n");
	for(i = 0 ; i < 2 ; i++)
		s(a);
	afficher_arbre(a);
	printf("Inversion de 2 éléments dans a : ech(a, 2, 3)\n");
	ech(a,2,3);
	afficher_arbre(a);
}
void nb_noeuds_feuilles()
{
	printf("\033[31mTest : nb_noeuds_feuilles\033[00m\n");
	int i;
	Abp a = lambda();
	for(i = 0 ; i < 6 ; i++)
		inser(a,i);

	printf("Nombre de nœuds : %d et de feuilles : %d\n",n(a), nf(a));
	printf("Suppression d'un élément\n");
	s(a);
	printf("Nombre de nœuds : %d et de feuilles : %d\n",n(a), nf(a));
	printf("Suppression d'un élément\n");
	s(a);
	printf("Nombre de nœuds : %d et de feuilles : %d\n",n(a), nf(a));
}

int main(int argc, char * argv[])
{
	ajout_suppression_echange();
	nb_noeuds_feuilles();
	return EXIT_SUCCESS;
}

