#ifndef __GRAPHE_H__
#define __GRAPHE_H__

typedef int RELATION;

typedef struct
{
	RELATION * relations;
} graphe_s;

graphe_s * nouveau_graphe(Nat taille);			// 
graphe_s * irg(RELATION * r);					// relation -> graphe
RELATION * igr(graphe_s * g);					// graphe -> relation
void adja(graphe_s * g, Nat a, Nat b);			// ajout arc
void supa(graphe_s * g, Nat a, Nat b);			// suppr. arc
int exa(graphe_s * g, Nat a, Nat b);			// test arc
RELATION * rv();								// relation vide
RELATION * relation_binaire_pleine();			// relation binaire pleine
RELATION * comp(RELATION * r1, RELATION * r2);	// composition
RELATION * sym(RELATION * r1);					// symétrie
RELATION * Un(RELATION * r1, RELATION * r2);	// union
RELATION * Intersection(RELATION * r1, RELATION * r2);

#endif

