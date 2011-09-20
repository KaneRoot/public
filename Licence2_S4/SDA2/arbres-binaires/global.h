/*
 *
 * 18/09/11
 *
 */

typedef enum { FAUX = 0, VRAI = 1 } bool;
typedef struct arbin
{
	struct arbin *g;
	int s;
	struct arbin *d;
} SARBIN;
