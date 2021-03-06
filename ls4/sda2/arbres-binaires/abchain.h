/* 
 *	abchain.h
 *
 */

void parcours_infixe(SARBIN * a, void (*pr)(int));
void parcours_prefixe(SARBIN * a, void (*pr)(int));
void postfixe(SARBIN * a, void (*pr)(int));
SARBIN * arbre_gauche(SARBIN *);
SARBIN * arbre_droit(SARBIN *);
int racine(SARBIN *);
bool vide(SARBIN *);
void ecrire(int);
SARBIN * creation_arbre_trie(int*,int);
SARBIN * insertion(SARBIN *,int);
void vidage(SARBIN *);
bool feuille(SARBIN *);
bool ega(SARBIN *,SARBIN *);
int max(int,int);
int hauteur(SARBIN *a);
/* PAS FAIT */
bool complet(SARBIN *);
SARBIN * enracinement(SARBIN *, int, SARBIN *);
SARBIN * recherche(SARBIN *, int);
SARBIN * arbre_vide();
SARBIN * extremite_gauche(SARBIN *);
SARBIN * extremite_droit(SARBIN *);
PAIRE * couper(SARBIN *, int);
PAIRE * creation_paire(SARBIN *, SARBIN *);
int nombre_noeuds(SARBIN *);
int nombre_feuilles(SARBIN *);
int nombre_noeuds_internes(SARBIN *);
