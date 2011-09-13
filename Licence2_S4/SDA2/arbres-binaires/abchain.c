#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abchain.h"

int main(int argc, char * argv[])
{
	SARBIN * truc = (SARBIN *) malloc(sizeof(SARBIN));
	truc->g =  (SARBIN *) malloc(sizeof(SARBIN));
	truc->d =  (SARBIN *) malloc(sizeof(SARBIN));
	*truc->g->s = 10;
	truc->s = 15;
	printf("%d ;\n",(*truc->g->s));
	free(truc);

	return EXIT_SUCCESS;
}

void infixe(SARBIN *a, void (*pr)(int))
{
	if( v(a) == FAUX )
	{
		infixe(ag(a),pr);
		(*pr)(r(a));
		infixe(ad(a),pr);
	}
}

SARBIN * ag(SARBIN *a)
{
	return a->g;
}
SARBIN * ad(SARBIN *a)
{
	return a->d;
}
int r(SARBIN *a)
{
	return a->s;
}
bool v(SARBIN *a)
{
	bool b = FAUX;
	if( a->s == -1)
		b = VRAI;

	return b;
}
