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

void afficher_po(Abp a)
{
	printf("L'arbre est-il partiellement ordonné ? ");
	if(po(a) == VRAI)
		printf("\033[31mOui\033[00m\n");
	else
		printf("\033[31mNon\033[00m\n");
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
void po_ipo_mont()
{
	printf("\033[31mTest : po_ipo_mont\033[00m\n");
	printf("	1 arbre 4 ajouts de 0 à 3, test po, puis ajouts de 0 et test po\n");
	Abp a = lambda();
	int i;
	for(i = 0 ; i < 4 ; i++)
		inser(a,i);
	afficher_arbre(a);
	afficher_po(a);
	inser(a,0);
	afficher_arbre(a);
	afficher_po(a);
	printf("	1 arbre 10 ajouts de 10 à 1 via ipo, test po\n"); //, puis ipo de 0 et test po\n");
	Abp b = lambda();
	for(i = 0 ; i < 10 ; i++)
		ipo(b, 10 - i);
	afficher_arbre(b);
	afficher_po(b);
}
int main(int argc, char * argv[])
{
	//ajout_suppression_echange();
	//nb_noeuds_feuilles();
	po_ipo_mont();
	return EXIT_SUCCESS;
}

