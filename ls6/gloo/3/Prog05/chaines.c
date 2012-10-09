#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void tmp()
{
	//  char chaine1[25]="Juste un petit exemple.";
	char nouvelle[11];
	char chaine2[25]="Juste un petit exemple.";

	strncpy(nouvelle, chaine2, 10);
	nouvelle[10] = '\0';
	printf("longueur de \"%s\" = %d\n",nouvelle, strlen(nouvelle));
}


void tab()
{
	int tableau[10000];
	int i;
	for(i=0; i<10000; i++) tableau[i]=-1;
}

int main()
{
	tab();
	tmp();
	return 0;
}

