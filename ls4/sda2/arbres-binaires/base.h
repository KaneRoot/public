/*
 *
 * 18/09/11
 *
 */


typedef unsigned int Nat;
typedef int Ent;
typedef float Rat;
typedef enum { FAUX = 0, VRAI = 1 } bool;

typedef struct arbin
{
	struct arbin *g;
	Nat s;
	struct arbin *d;
} SARBIN, *Arbin;

typedef struct paire
{
	struct arbin *a;
	struct arbin *b;
} PAIRE;
