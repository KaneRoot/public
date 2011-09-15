/*
 * arbin.c
 *
 * 13/09/11
 *
 */
#include "abchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_ELEMENTS_ARBRE 30

int main(int argc, char * argv[])
{
	int i = 0;
	int *x = (int *) malloc(sizeof(int*)*NB_ELEMENTS_ARBRE);
	for(i = 0 ; i < NB_ELEMENTS_ARBRE ; i++)
		*(x + i) = (i * 9) ;
	SARBIN * truc;
	fprintf(stdout, "Création de l'arbre\n");
	fprintf(stdout, "-------------------\n");
	truc = creation_arbre_trie(x);
	fprintf(stdout, "Parcours de l'arbre\n");
	fprintf(stdout, "-------------------\n");
	infixe(truc, ecrire);

	free(x);
	vidage(truc);

	return EXIT_SUCCESS;
}

void infixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		infixe(ag(a),pr);
		(*pr)(r(a));
		infixe(ad(a),pr);
	}
}

SARBIN * ag(SARBIN *a)
{
	return a->g;
}
SARBIN * ad(SARBIN *a)
{
	return a->d;
}
int r(SARBIN *a)
{
	return a->s;
}
bool v(SARBIN *a)
{
	return (a == NULL) ? VRAI : FAUX;
}
SARBIN * creation_noeud()
{
	SARBIN * a = (SARBIN *) malloc(sizeof(SARBIN));
	a->s = -1;
	a->g = NULL;
	a->d = NULL;
	return a;
}
void ecrire(int x)
{
	printf(" %d \n", x);
}
SARBIN * creation_arbre_trie(int *x)
{
	SARBIN * tmp = creation_noeud();
	int i;

	for(i = 0 ; i < NB_ELEMENTS_ARBRE; i++)
	{
		tmp = insr(tmp,*(x + i));
	}
	return tmp;
}
SARBIN * insr(SARBIN * a, int x)
{
	printf("insr : %d\n", x);
	if( v(a) == VRAI )
	{
		a = creation_noeud();
		a->s = x;
	}
	else if(a->s > x)
		 a->g = insr(ag(a),x);
	else
		 a->d = insr(ad(a),x);

	return a;
}

void vidage(SARBIN * a)
{
		if( v(a) == FAUX )
		{
			vidage(ag(a));
			vidage(ad(a));
			free(a);
		}
}
