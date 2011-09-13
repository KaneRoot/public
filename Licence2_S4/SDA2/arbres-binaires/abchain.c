#include "abchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	SARBIN * truc = creation_arbin();
	printf("%d ;\n", truc->s);
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
	return (a == NULL) ? VRAI : FAUX;
}
SARBIN * creation_arbin()
{
	SARBIN * a = (SARBIN *) malloc(sizeof(SARBIN));
	a->s = -1;
	a->g = NULL;
	a->d = NULL;
	return a;
}
