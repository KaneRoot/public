#include "base.h"
#include "arbinom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	Arbinom * a = lier(feuille(3),feuille(15));
	printf("hauteur de a : %d\n", hauteur(a));
	printf("hauteur de premier_fils(a) : %d\n", hauteur(premier_fils(a)));
	printf("hauteur de autres_fils(a) : %d\n", hauteur(autres_fils(a)));
	printf("est_feuille de a : %d\n", est_feuille(a));
	printf("est_feuille de feuille(x) : %d\n", est_feuille(feuille(1)));
	printf("racine de a : %d\n", racine(a));
	printf("nombre_noeuds_internes de a : %d\n", nombre_noeuds_internes(a));
	printf("nombre_noeuds de a : %d\n", nombre_noeuds(a));
	printf("nombre_feuilles de a : %d\n", nombre_feuilles(a));
	printf("Affichage de a : \n");
	affichage(a);
	return EXIT_SUCCESS;
}
/* fonctions de base */
Arbinom * enracinement(Arbinom * a1, Arbinom * a2, Ent x)
{
	Arbinom * a;
	if((a = malloc(sizeof(Arbinom))) != NULL)
	{
		a->premier_fils = a1;
		a->autres_fils = a2;
		a->s = x;
	}
	else
	{
		fprintf(stderr, "Erreur malloc lier\n");
		exit(EXIT_FAILURE);
	}
	
	return a;
}
Arbinom * lier(Arbinom * a1, Arbinom * a2)
{
	/* Quelques affichages pour voir ce qu'il se passe.
	printf("Liaison :: racine : %d\n",racine(a1));
	printf("Affichage a1\n");
	affichage(a1);
	printf("Affichage a2\n");
	affichage(a2);
	*/
	Arbinom *a3 = enracinement(premier_fils(a1), premier_fils(a2), racine(a1));
	return enracinement(a3, arbre_vide(), racine(a1));
}
Arbinom * feuille(Ent x)
{
	return enracinement(arbre_vide(), arbre_vide(), x);
}
Ent racine(Arbinom *a)
{
	return (a == NULL) ? -1 : (est_feuille(a)) ? a->s : racine(autres_fils(a));
}
void affichage(Arbinom *a)
{
	if(a == NULL)
		return;
	printf("Racine : %d\nPremiers fils\n",a->s);
	affichage(premier_fils(a));
	printf("Autres fils\n");
	affichage(autres_fils(a));

}
Arbinom * premier_fils(Arbinom *a)
{
	return (a == NULL) ? arbre_vide() : (Arbinom *) a->premier_fils;
}
Arbinom * autres_fils(Arbinom *a)
{
	return (a == NULL) ? arbre_vide() : (Arbinom *) a->autres_fils;
}
bool est_feuille(Arbinom * a)
{
	return (a==NULL) ? FAUX : (premier_fils(a) == arbre_vide() && autres_fils(a) == arbre_vide());
}
Arbinom * arbre_vide()
{
	return (Arbinom *) NULL;
}

/* autres fonctions */
Ent nombre_noeuds(Arbinom *a)
{
	return (a == NULL) ? -1 : (est_feuille(a)) ? 1 : 
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
	return (a == NULL) ? -1 : (est_feuille(a)) ? 0 : 1 + 2 * nombre_noeuds_internes(premier_fils(a));
}
Ent hauteur(Arbinom *a)
{	// Si hauteur == -1 : erreur
	return (a == NULL) ? -1 : (est_feuille(a)) ? 0 : 1 + hauteur(premier_fils(a));
}
