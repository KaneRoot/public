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
//	test1();
//	test_feuille();
//	test_ega();
//	test_hauteur();
//	test_extremites();

	return EXIT_SUCCESS;
}


void infixe(SARBIN *a, void (*pr)(int))
{
	if( vide(a) == FAUX )
	{
		infixe(arbre_gauche(a),pr);
		(*pr)(racine(a));
		infixe(arbre_droit(a),pr);
	}
}
void prefixe(SARBIN *a, void (*pr)(int))
{
	if( vide(a) == FAUX )
	{
		(*pr)(racine(a));
		prefixe(arbre_gauche(a),pr);
		prefixe(arbre_droit(a),pr);
	}
}

void postfixe(SARBIN *a, void (*pr)(int))
{
	if( vide(a) == FAUX )
	{
		postfixe(arbre_gauche(a),pr);
		postfixe(arbre_droit(a),pr);
		(*pr)(racine(a));
	}
}
SARBIN * arbre_gauche(SARBIN *a)
{
	return a->g;
}
SARBIN * arbre_droit(SARBIN *a)
{
	return a->d;
}
int racine(SARBIN *a)
{
	return a->s;
}
bool vide(SARBIN *a)
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
		tmp = insertion(tmp,*(x + i));

	return tmp;
}
SARBIN * insertion(SARBIN * a, int x)
{
	if( vide(a) == VRAI )
	{
		a = enracinement(NULL, x, NULL);
	}
	else if(a->s > x)
		a->g = insertion(arbre_gauche(a),x);
	else
		a->d = insertion(arbre_droit(a),x);

	return a;
}

void vidage(SARBIN * a)
{
	if( vide(a) == FAUX )
	{
		vidage(arbre_gauche(a));
		vidage(arbre_droit(a));
		free(a);
	}
}
bool feuille(SARBIN *a)
{
	return (vide(a)) ? FAUX : (vide(arbre_gauche(a)) && vide(arbre_droit(a))) ? VRAI : FAUX;
}
bool ega(SARBIN * a1, SARBIN * a2)
{
	bool res = VRAI;
	if(vide(a1) && vide(a2))
		res = VRAI;
	else if(vide(a1) != vide(a2))
		res = FAUX;
	else
	{
		if(a1->s != a2->s || 
				ega(arbre_gauche(a1),arbre_gauche(a2)) == FAUX || 
				ega(arbre_droit(a1),arbre_droit(a2)) == FAUX)
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
	if( ! vide(a))
	{
		i = 1 + max(hauteur(arbre_gauche(a)),hauteur(arbre_droit(a)));
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
	if(vide(a))
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
			tmp = recherche(arbre_droit(a),x);
	}
	return tmp;
}
SARBIN * arbre_vide()
{
	return NULL;
}
SARBIN * extremite_gauche(SARBIN *a)
{
	SARBIN * tmp = NULL;
	if(! vide(a) && ! vide(arbre_gauche(a)))
		tmp = extremite_gauche(arbre_gauche(a));
	else
		tmp = a;
	return tmp;
}
SARBIN * extremite_droit(SARBIN *a)
{
	SARBIN * tmp = NULL;
	if(! vide(a) && ! vide(arbre_droit(a)))
	{
		printf("RACINE a : %d\n",racine(a));
		tmp = extremite_droit(arbre_droit(a));
	}
	else
	{
		printf("ELSE\n");
		tmp = a;
	}
	return tmp;
}
