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
	if(feuille(ad(arbin)) == VRAI)
		printf("FEUILLE AD(ARBIN) == VRAI ; JUSTE \n");

	vidage(arbin);
}
void test_ega()
{
	int x1[] = { 14, 35 };
	int x2[] = { 14, 35, 28 };
	int x3[] = { 14, 28, 35 };
	int x4[] = { 14, 28, 35, 35 };

	SARBIN * a1 = creation_arbre_trie(x1,2);
	SARBIN * a2 = creation_arbre_trie(x1,2);
	SARBIN * a3 = creation_arbre_trie(x2,3);
	SARBIN * a4 = creation_arbre_trie(x3,3);
	SARBIN * a5 = creation_arbre_trie(x4,4);

	assertion_ega(a1,a2,VRAI);
	assertion_ega(a1,a3,FAUX);
	assertion_ega(a3,a4,FAUX);
	assertion_ega(a4,a5,FAUX);

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
