#include "base.h"
#include "arbinom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	return EXIT_SUCCESS;
}
/* fonctions de base */
Arbinom * lier(Arbinom * a1, Arbinom * a2)
{
	Arbinom * a;
	if((a = malloc(sizeof(Arbinom))) != NULL)
	{
		a->premier_fils = a1;
		a->autres_fils = a2;
	}
	else
	{
		fprintf(stderr, "Erreur malloc lier\n");
		exit(EXIT_FAILURE);
	}
	
	return a;
}
Arbinom * feuille(Ent x)
{
	Arbinom * a = NULL;
	if((a = malloc(sizeof(Arbinom))) != NULL)
	{
		a->premier_fils = NULL;
		a->autres_fils = NULL;
		a->s = x;
	}
	else
	{
		fprintf(stderr, "Erreur malloc feuille\n");
		exit(EXIT_FAILURE);
	}

	return a;
}
Ent racine(Arbinom *a)
{
	return (est_feuille(a)) ? a->s : racine(premier_fils(a));
}
Arbinom * premier_fils(Arbinom *a)
{
	return (Arbinom *) a->premier_fils;
}
Arbinom * autres_fils(Arbinom *a)
{
	return (Arbinom *) a->autres_fils;
}
bool est_feuille(Arbinom * a)
{
	return (a==NULL) ? FAUX : (premier_fils(a) == NULL && autres_fils(a) == NULL);
}

/* autres fonctions */
Ent nombre_noeuds(Arbinom *a)
{
	return (est_feuille(a)) ? 1 : 
		nombre_feuilles(premier_fils(a)) + nombre_feuilles(autres_fils(a));
}
Ent nombre_feuilles(Arbinom *a)
{
	int i, nn = 1, h = hauteur(a);
	for(i = 0 ; i < h ; i++)
		nn *= 2;
	return nn;
}
Ent nombre_noeuds_internes(Arbinom *a)
{
	return (est_feuille(a)) ? 0 : 1 + 2 * nombre_noeuds_internes(premier_fils(a));
}
Ent hauteur(Arbinom *a)
{
	return (a == NULL) ? -1 : (est_feuille(a)) ? 0 : 1 + hauteur(premier_fils(a));
}

/* pas implanté */
