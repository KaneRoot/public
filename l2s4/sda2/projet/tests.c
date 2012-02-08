#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "ABP.h"
#include "ABPO0.h"
#include "ABPO1.h"

void afficher_nb_noeuds(Abp a)
{
	printf("	Nombre de nœuds : %d et de feuilles : %d\n",n(a), nf(a));
}
void afficher_arbre(Abp a)
{
	int i;
	printf("\033[31m[\033[00m ");
	for(i = 0 ; i < n(a)-1 ; i++)
		printf("%2.1f | ",v(a,i));
	if(n(a) > 0) 
		printf("%2.1f \033[31m]\033[00m\n",v(a,n(a)-1));
	else
		printf("\033[31m]\033[00m\n");
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
	printf("\n\033[31mTest : ajout_suppression_echange\033[00m\n");
	printf("	Ajout de 6 valeurs à un arbre a\n");
	int i;
	Abp a = lambda();
	for(i = 0 ; i < 6 ; i++)
		inser(a,i);
	afficher_arbre(a);
	printf("	Suppression de 2 éléments dans l'arbre a\n");
	for(i = 0 ; i < 2 ; i++)
		s(a);
	afficher_arbre(a);
	printf("	Inversion de 2 éléments dans a : ech(a, 2, 3)\n");
	ech(a,2,3);
	afficher_arbre(a);
	printf("	Remplacer l'élément à l'emplacement 1 par 6\n");
	a = r(a,1,6);
	afficher_arbre(a);
	printf("	Remplacer l'élément à l'emplacement 8 par 1\n");
	a = r(a,8,1);
	afficher_arbre(a);
}
void nb_noeuds_feuilles()
{
	printf("\n\033[31mTest : nb_noeuds_feuilles\033[00m\n");
	printf("	Ajout de 6 éléments à un arbre a\n");
	int i;
	Abp a = lambda();
	for(i = 0 ; i < 6 ; i++)
		inser(a,i);
	afficher_arbre(a);
	afficher_nb_noeuds(a);
	printf("Suppression d'un élément\n");
	s(a);
	afficher_nb_noeuds(a);
	printf("Suppression d'un élément\n");
	s(a);
	afficher_nb_noeuds(a);
}
void po_ipo_mont()
{
	printf("\n\033[31mTest : po_ipo_mont\033[00m\n");
	printf("	Un arbre 'a' auquel je fais 10 ajouts de 10 à 1 via 'i' \n");
	Abp a = lambda();
	int i;
	for(i = 0 ; i < 10 ; i++)
		inser(a,10-i);
	afficher_arbre(a);
	afficher_po(a);
	printf("\n	Un arbre 'b' auquel je fais 10 ajouts de 10 à 1 via 'ipo'\n");
	Abp b = lambda();
	for(i = 0 ; i < 10 ; i++)
		ipo(b, 10 - i);
	afficher_arbre(b);
	afficher_po(b);
	printf("	Test v(b,imont(2)) : %2.1f\n",v(b,imont(2)));
	printf("	Test v(b,imont(6)) : %2.1f\n",v(b,imont(6)));
}
void spo_desc_imin()
{
	printf("\n\033[31mTest : spo_desc_imin\033[00m\n");
	printf("	Un arbre 'a' de 10 éléments de 10 à 1 via ipo\n");
	Abp a = lambda();
	int i;
	for(i = 0 ; i < 10 ; i++) ipo(a,10-i);
	afficher_arbre(a);
	afficher_po(a);
	printf("Suppression de l'élément 3\n");
	spo(a,3);
	afficher_arbre(a);
	afficher_po(a);
	afficher_nb_noeuds(a);
	printf("Ajout de l'élément -1\n");
	ipo(a,-1);
	afficher_arbre(a);
	printf("Suppression de l'élément 2\n");
	spo(a,2);
	afficher_arbre(a);
	afficher_po(a);
	printf("	Test v(a,imin(a,2)) : %2.1f\n",v(a,imin(a,2)));
	printf("	Test v(a,imin(a,6)) : %2.1f\n",v(a,imin(a,6)));
}
int main(int argc, char * argv[])
{
	ajout_suppression_echange();
	nb_noeuds_feuilles();
	po_ipo_mont();
	spo_desc_imin();

	return EXIT_SUCCESS;
}

