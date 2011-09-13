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

int main(int argc, char * argv[])
{
	int i = 0;
	int *x = (int *) malloc(sizeof(int*)*10);
	for(i = 0 ; i < 9 ; i++)
		*(x + i) = i+ 10;
	x[9] = NULL;
	SARBIN * truc;
	//printf("%d \n", truc->s);
	fprintf(stdout, "Création de l'arbre\n");
	fprintf(stdout, "-------------------\n");
	truc = creation_arbre_trie(x);
	fprintf(stdout, "Parcours de l'arbre\n");
	fprintf(stdout, "-------------------\n");
	infixe(truc, ecrire);

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
	for(i = 0 ; *(x + i) != NULL ; i++)
	{
		tmp = insr(tmp,*(x + i));
	}
	return tmp;
}
SARBIN * insr(SARBIN * a, int x)
{
	SARBIN * res = a;
	if( v(res) == VRAI )
	{
		res = creation_noeud();
		res->s = x;
	}
	else if(res->s > x)
		 res->g = insr(ag(res),x);
	else
		 res->d = insr(ad(res),x);

	return res;
}
