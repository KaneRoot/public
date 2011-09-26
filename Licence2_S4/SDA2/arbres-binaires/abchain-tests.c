#include "base.h"
#include "abchain-tests.h"
#include "abchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_ELEMENTS_ARBRE 5

void test1()
{
	int i = 0;
	int *x = (int *) malloc(sizeof(int*)*NB_ELEMENTS_ARBRE);
	for(i = 0 ; i < NB_ELEMENTS_ARBRE ; i++)
		*(x + i) = (i * 9) ;
	SARBIN * truc;
	fprintf(stdout, "Création de l'arbre\n");
	fprintf(stdout, "-------------------\n");
	truc = creation_arbre_trie(x,NB_ELEMENTS_ARBRE);
	fprintf(stdout, "Parcours de l'arbre");
	fprintf(stdout, "\n------INFIXE-------\n");
	infixe(truc, ecrire);
	fprintf(stdout, "\n------PREFIXE------\n");
	prefixe(truc, ecrire);
	fprintf(stdout, "\n------POSTFIXE-----\n");
	postfixe(truc, ecrire);

	fprintf(stdout, "\n-FIN DU PROGRAMME-\n");
	free(x);
	vidage(truc);
}
void test_feuille()
{
	int x[] = { 14, 35 };
	SARBIN * arbin = creation_arbre_trie(x,2);
	printf("INFIXE arbin\n");
	infixe(arbin,ecrire);
	printf("\n");

	if(feuille(arbin) == VRAI)
		printf("FEUILLE ARBIN - ERREUR\n");
	if(feuille(arbre_droit(arbin)) == VRAI)
		printf("FEUILLE AD(ARBIN) == VRAI ; JUSTE \n");

	vidage(arbin);
}
void test_ega()
{
	int x[] = {};
	int x1[] = { 14, 35 };
	int x2[] = { 14, 35, 28 };
	int x3[] = { 14, 28, 35 };
	int x4[] = { 14, 28, 35, 35 };

	SARBIN * a1 = creation_arbre_trie(x1,2);
	SARBIN * a2 = creation_arbre_trie(x1,2);
	SARBIN * a3 = creation_arbre_trie(x2,3);
	SARBIN * a4 = creation_arbre_trie(x3,3);
	SARBIN * a5 = creation_arbre_trie(x4,4);
	SARBIN * a = creation_arbre_trie(x,0);

	assertion_ega(a1,a2,VRAI);
	assertion_ega(a1,a3,FAUX);
	assertion_ega(a3,a4,FAUX);
	assertion_ega(a4,a5,FAUX);
	assertion_ega(a,a,VRAI);
	assertion_ega(a, a2, FAUX);

	vidage(a1);
	vidage(a2);
	vidage(a3);
	vidage(a4);
	vidage(a5);
}
void assertion_ega(SARBIN * a1, SARBIN * a2, bool b)
{
	if(ega(a1,a2) != b)
		fprintf(stderr, "Erreur ega\n");
	else
		fprintf(stdout, "OK\n");
}
void test_hauteur()
{
	int x[] = { 15 };
	SARBIN * a = creation_arbre_trie(x, 1);
	printf("Hauteur trouvée %d\n",hauteur(a));
	vidage(a);
}
void test_completude()
{
	int x[] = { 15,10,14 };
	SARBIN * a = creation_arbre_trie(x, 3);
	assertion_completude(a,VRAI);
}
void assertion_completude(SARBIN * a, bool b)
{
	if( complet(a) == b)
		fprintf(stdout, "completude : OK\n");
	else
		fprintf(stderr, "complétude : ERREUR\n");
}
void test_extremites()
{
	int x[] = { 14, 16, 30, 20, 25 };
	SARBIN * a = creation_arbre_trie(x, 5);
	SARBIN * b = extremite_droit(a);
	infixe(a,ecrire);
	printf("\n");
	infixe(b,ecrire);
	printf("\n");
	printf("Extremite droit : %d \n",racine(b));
	vidage(a);
}
