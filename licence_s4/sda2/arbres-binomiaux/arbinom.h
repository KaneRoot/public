#ifndef ARBINOM
#define ARBINOM

/* structures */
typedef struct arbinom
{
	struct arbinom * premier_fils;
	struct arbinom * autres_fils;
	Nat x;
} Arbinom;

/* prototypes */
Ent nombre_noeuds(Arbinom *a);
Ent nombre_noeuds_internes(Arbinom *a);
Ent nombre_feuilles(Arbinom *a);
Ent racine(Arbinom * a);
bool est_feuille(Arbinom *a);
Arbinom * arbre_vide();
Arbinom * lier(Arbinom * a1, Arbinom * a2);
Arbinom * feuille(Ent x);
Ent hauteur(Arbinom *a);
Arbinom * premier_fils(Arbinom *a);
Arbinom * autres_fils(Arbinom *a);

#endif
