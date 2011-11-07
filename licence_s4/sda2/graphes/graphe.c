#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

typedef Rel int[];

typedef struct
{
	 * relations;
	int n;
} graphe_s;

graphe_s * irg(rel * r)
{
}
Rel * igr(graphe_s * g)
{
}
void adja(graphe_s * g, Nat a, Nat b)
{
	if(a >= 0 && b >= 0)
		g.relations[a*b] = VRAI;
}
void supa(graphe_s * g, Nat a, Nat b)
{
	if(a >= 0 && b >= 0)
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

