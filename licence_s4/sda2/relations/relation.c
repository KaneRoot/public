#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

#define TAILLE 4

typedef int RELATION;

typedef struct
{
	RELATION * relations;
} graphe_s;

RELATION * nouvelle_relation()
{
	return (RELATION *) malloc(sizeof(RELATION) * TAILLE* TAILLE);
}
graphe_s * nouveau_graphe()
{
	int i;
	graphe_s * g = NULL;
	g = malloc(sizeof(graphe_s));
	if(g == NULL)
	{
		fprintf(stderr, "malloc(sizeof(graphe_s)) -- error\n");
		exit(EXIT_FAILURE);
	}
	g->relations = (RELATION *) malloc(sizeof(int)*TAILLE*TAILLE);
	if(g->relations == NULL)
	{
		fprintf(stderr, "malloc(sizeof(int)*TAILLE*TAILLE) -- error\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < TAILLE*TAILLE ; i++)
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
void adja(RELATION * r, Nat a, Nat b)
{
	if(a >= 0 && b >= 0 && a < TAILLE && b < TAILLE)
		r[a*b] = VRAI;
}
void supa(RELATION * r, Nat a, Nat b)
{
	if(a >= 0 && b >= 0 && a < TAILLE && b < TAILLE)
		r[a*b] = FAUX;
}
int exa(RELATION * r, Nat a, Nat b)
{
	if(a < 0 || b < 0)
		return -1;
	return r[a*b];
}


// Fait en cours
RELATION * rv()
{
	return (RELATION*) NULL;
}

RELATION * comp(RELATION * r1, RELATION * r2)
{
	Nat i, j, k;
	RELATION * r3 = rv(); // Relation vide
	bool x = FAUX;
	
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0 ; j < TAILLE ; j++)
		{
			for(k = 0 ; k < TAILLE ; k++)
			{
				x = x || (exa(r1,i,k) && exa(r2,k,j));
			}
			if(x)
				adja(r3,i,j);
		}
	}
	return r3;
}
RELATION * sym(RELATION * r1)
{
	Nat	i, j;
	RELATION * r2 = nouvelle_relation();
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0; j < TAILLE ; j++)
		{
			if(exa(r1,i,j))
				adja(r2,j,i);
		}
	}
	return r2;
}
// Union
RELATION * Un(RELATION * r1, RELATION * r2)
{
	Nat i, j;
	RELATION * r3 = nouvelle_relation();
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0; j < TAILLE ; j++)
		{
			if(exa(r1,i,j) && exa(r2,i,j))
				adja(r3,i,j);
		}
	}
	return r3;
}
void write_relation(RELATION * r)
{
	int i, j;
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0; j < TAILLE ; j++)
			printf("r[N*%d+%d] = %d | ", i, j, r[TAILLE*i + j]);
		printf("\n");
	}
}

int main(int argc, char * argv[])
{
	RELATION * r = nouvelle_relation();
	write_relation(r);
	return EXIT_SUCCESS;
}
