/*
 * arbin.c
 *
 * 13/09/11
 *
 */
#include "abchain.h"
#include "abchain-tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	//test1();
	//test_feuille();
	test_ega();
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
void prefixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		(*pr)(r(a));
		prefixe(ag(a),pr);
		prefixe(ad(a),pr);
	}
}

void postfixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		postfixe(ag(a),pr);
		postfixe(ad(a),pr);
		(*pr)(r(a));
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
bool feuille(SARBIN *a)
{
	return (v(a)) ? FAUX : (v(ag(a)) && v(ad(a))) ? VRAI : FAUX;
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
				ega(ag(a1),ag(a2)) == FAUX || 
				ega(ad(a1),ad(a2)) == FAUX)
			res = FAUX;
	}

	return res;
}
