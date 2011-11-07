#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

#define TAILLE 15

typedef int RELATION;

typedef struct
{
	RELATION * relations;
} graphe_s;

graphe_s * nouveau_graphe(Nat taille)
{
	int i;
	graphe_s * g = NULL;
	g = malloc(sizeof(graphe_s));
	if(g == NULL)
	{
		fprintf(stderr, "malloc(sizeof(graphe_s)) -- error\n");
		exit(EXIT_FAILURE);
	}
	g->relations = (RELATION *) malloc(sizeof(int)*taille*taille);
	if(g->relations == NULL)
	{
		fprintf(stderr, "malloc(sizeof(int)*taille*taille) -- error\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < taille*taille ; i++)
		g->relations[i] = 0;
	return g;
}
graphe_s * irg(RELATION * r) 
{
	graphe_s * g = nouveau_graphe(TAILLE);
	free(g->relations);
	g->relations = r;

	return g;
}
RELATION * igr(graphe_s * g) {
	return g->relations;
}
void adja(graphe_s * g, Nat a, Nat b)
{
	if(a >= 0 && b >= 0 && a < TAILLE && b < TAILLE)
		g->relations[a*b] = VRAI;
}
void supa(graphe_s * g, Nat a, Nat b)
{
	if(a >= 0 && b >= 0 && a < TAILLE && b < TAILLE)
		g->relations[a*b] = FAUX;
}
int exa(graphe_s * g, Nat a, Nat b)
{
	if(a < 0 || b < 0)
		return -1;
	return g->relations[a*b];
}

int main(int argc, char * argv[])
{
	return EXIT_SUCCESS;
}

// Fait en cours

Rel * comp(Rel * r1, Rel * r2)
{
	Nat i, j, k;
	Rel * r3 = rv(); // Relation vide
	bool x = FAUX;
	
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(k = 0 ; k < TAILLE ; k++)
		{
			x = x || (ea(r1,i,k) && ea(r2,k,j));
		}
		if(x)
			r3 = aa(r3,i,j);
		}
	}
	return r3;
}
