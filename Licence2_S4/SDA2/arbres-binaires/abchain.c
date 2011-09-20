/*
 * arbin.c
 *
 * 13/09/11
 *
 */
#include "global.h"
#include "abchain.h"
#include "abchain-tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	//test1();
	//test_feuille();
	//test_ega();
	//test_hauteur();
	return EXIT_SUCCESS;
}


void infixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		infixe(arbre_gauche(a),pr);
		(*pr)(racine(a));
		infixe(ad(a),pr);
	}
}
void prefixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		(*pr)(racine(a));
		prefixe(arbre_gauche(a),pr);
		prefixe(ad(a),pr);
	}
}

void postfixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		postfixe(arbre_gauche(a),pr);
		postfixe(ad(a),pr);
		(*pr)(racine(a));
	}
}
SARBIN * arbre_gauche(SARBIN *a)
{
	return a->g;
}
SARBIN * ad(SARBIN *a)
{
	return a->d;
}
int racine(SARBIN *a)
{
	return a->s;
}
bool v(SARBIN *a)
{
	return (a == NULL) ? VRAI : FAUX;
}
void ecrire(int x)
{
	printf(" %d :", x);
}
SARBIN * creation_arbre_trie(int *x, int nb_elements)
{
	SARBIN * tmp = NULL;
	int i;

	for(i = 0 ; i < nb_elements ; i++)
		tmp = insr(tmp,*(x + i));

	return tmp;
}
SARBIN * insr(SARBIN * a, int x)
{
	if( v(a) == VRAI )
	{
		a = enracinement(NULL, x, NULL);
	}
	else if(a->s > x)
		a->g = insr(arbre_gauche(a),x);
	else
		a->d = insr(ad(a),x);

	return a;
}

void vidage(SARBIN * a)
{
	if( v(a) == FAUX )
	{
		vidage(arbre_gauche(a));
		vidage(ad(a));
		free(a);
	}
}
bool feuille(SARBIN *a)
{
	return (v(a)) ? FAUX : (v(arbre_gauche(a)) && v(ad(a))) ? VRAI : FAUX;
}
bool ega(SARBIN * a1, SARBIN * a2)
{
	bool res = VRAI;
	if(v(a1) && v(a2))
		res = VRAI;
	else if(v(a1) != v(a2))
		res = FAUX;
	else
	{
		if(a1->s != a2->s || 
				ega(arbre_gauche(a1),arbre_gauche(a2)) == FAUX || 
				ega(ad(a1),ad(a2)) == FAUX)
			res = FAUX;
	}

	return res;
}
int max(int a, int b)
{
	return (a>b) ? a : b;
}
int hauteur(SARBIN *a)
{
	int i = -1;
	if( ! v(a))
	{
		i = 1 + max(hauteur(arbre_gauche(a)),hauteur(ad(a)));
	}
	return i;	
}
bool complet(SARBIN *a)
{
	return VRAI;
}
SARBIN * enracinement(SARBIN *g, int x, SARBIN * d)
{
	SARBIN * a = (SARBIN *) malloc(sizeof(SARBIN));
	a->s = x;
	a->g = g;
	a->d = d;
	return a;
}
SARBIN * recherche(SARBIN * a, int x)
{
	SARBIN * tmp = NULL;
	if(v(a))
	{
		tmp = arbre_vide();
	}
	else
	{
		if(racine(a) > x)
			tmp = recherche(arbre_gauche(a),x);
		else if(racine(a) == x)
			tmp = a;
		else
			tmp = recherche(ad(a),x);
	}
	return tmp;
}
SARBIN * arbre_vide()
{
	return NULL;
}
