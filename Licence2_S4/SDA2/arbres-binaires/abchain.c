#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arbin
{
	struct SARBIN *g;
	int s;
	struct SARBIN *d;
} SARBIN;
typedef SARBIN * sarbin;

void main(int argc, char * argv[])
{
	sarbin truc = (sarbin) malloc(sizeof(sarbin));
	truc->s = 15;
	printf("%d ;\n",truc->s);
	exit(EXIT_SUCCESS);
}
