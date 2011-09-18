/* 
 *	abchain.h
 *	
 *	13/09/11
 */

typedef enum { FAUX, VRAI=1 } bool;
typedef struct arbin
{
	struct SARBIN *g;
	int s;
	struct SARBIN *d;
} SARBIN;

void infixe(SARBIN * a, void (*pr)(int));
void prefixe(SARBIN * a, void (*pr)(int));
void postfixe(SARBIN * a, void (*pr)(int));
SARBIN * ag(SARBIN *);
SARBIN * ad(SARBIN *);
int r(SARBIN *);
bool v(SARBIN *);
SARBIN * creation_noeud(void);
void ecrire(int);
SARBIN * creation_arbre_trie(int*,int);
SARBIN * insr(SARBIN *,int);
void vidage(SARBIN *);
bool feuille(SARBIN *);
bool ega(SARBIN *,SARBIN *);
