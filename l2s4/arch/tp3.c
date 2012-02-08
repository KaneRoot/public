#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n(int a)
{
	return (a + 1)%2;
}
void table_de_verite()
{
	int i,j,k;
	// table de vérité &
	printf("a b c\n");
	for(i = 0; i < 2 ; i++)
	{
		for(j = 0; j < 2 ; j++)
		{
			for(k = 0 ; k < 2 ; k++)
			{
				printf("%d %d %d = %d : %d \n", i, j , k,
					(n(i)&n(j)&k)|
					(n(i)&j&n(k))|
					(i&n(j)&n(k))|
					(i&n(j)&k)|
					(i&j&n(k)),
					(i&n(j))|
					(j&n(k))|
					(n(j)&k)
					  );
			}
		}
	}
}

int main(int argc, char * argv[])
{
	table_de_verite();
	return EXIT_SUCCESS;
}

/* Pour la lecture interactive
char * supprimer(char * chaine, char c)
{
	int taille = 0,i,k;

	for(i = 0 ; i < strlen(chaine) ; i++)
		if(chaine[i] != c) taille++;

	char * nouvellechaine = malloc(sizeof(char) * taille +1);
	for(i = 0 ; i < taille ; i++)
		nouvellechaine[i] = '\0';
	for(k = 0,i=0 ; k < strlen(chaine) ; k++)
	{
		if(chaine[k] != c)
		{
			nouvellechaine[i] = chaine[k];
			i++;
		}
	}
	return nouvellechaine;		
}
int trad_expression(int a, int b, int c, char * expression)
{
	int i,courant;
	int taille = strlen(expression);
	// évaluation des NON
	for(i = 0 ; i < taille; i++)
	{
		if(expression[i] == '/')
		{
			if(expression[i+1] == 'a') a = (a + 1) %2;
			if(expression[i+1] == 'b') b = (b + 1) %2;
			if(expression[i+1] == 'c') c = (c + 1) %2;
		}
	}
	char * nouvellechaine = supprimer(expression, '/');
	// évaluation des . et +
	for(i = 0 ; i < strlen(nouvellechaine) ; i++)
	{
		if(nouvellechaine[i] == '.')
		{
		}
	}
	
}
*/
