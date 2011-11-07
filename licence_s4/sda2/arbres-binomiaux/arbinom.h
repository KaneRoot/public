#ifndef ARBINOM
#define ARBINOM

/* structures */
typedef struct arbinom
{
	struct arbinom * premier_fils;
	struct arbinom * autres_fils;
	Ent s;
} Arbinom;

/* prototypes */

// nn
Ent nombre_noeuds(Arbinom *a);
// ni
Ent nombre_noeuds_internes(Arbinom *a);
// nf
Ent nombre_feuilles(Arbinom *a);
// r
Ent racine(Arbinom * a);
// ef
bool est_feuille(Arbinom *a);
// ^
Arbinom * arbre_vide();
// l
Arbinom * lier(Arbinom * a1, Arbinom * a2);
// f
Arbinom * feuille(Ent x);
// h
Ent hauteur(Arbinom *a);
// pf
Arbinom * premier_fils(Arbinom *a);			
// af
Arbinom * autres_fils(Arbinom *a);

void affichage(Arbinom *a);

#endif
