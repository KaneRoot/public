#include <stdlib.h>     
#include <stdio.h>     

#define N 1000

typedef struct cell {
	int           valeur;
	struct cell * suivant;
} Cellule;


Cellule * cons(Cellule * liste, int valeur)
{
	Cellule * new_cell = malloc(sizeof(Cellule));
	new_cell->valeur  = valeur;
	new_cell->suivant = liste;
	return new_cell;
}

Cellule * insertion(Cellule * org, int val)
{
	Cellule * new_cell = cons(NULL,val);
	Cellule * tete = org;

	if (org==NULL)
		return new_cell;

	if (val<org->valeur){
		new_cell->suivant = org;
		return new_cell;
	}

	while((org->suivant!=NULL)&&(org->suivant->valeur<val))
		org = org->suivant;

	new_cell->suivant = org->suivant;
	org->suivant = new_cell;

	return tete;
}

int main()
{
	int fib1=1, fib2=1;
	int n=1, i, tmp;
	Cellule * table_hachage[N];

	for(i=0; i<N; i++) table_hachage[i] = NULL;

	for(n=1; n<100; n++)
	{
		/* calcul de fibonacci*/
		tmp = fib2;
		fib2 = fib1+fib2;
		fib1 = tmp;

		/* n%40 prend des valeurs entre 0 et 39 */
		// Cela peut prendre des valeurs négatives, puisque nous avons des entiers signés
		table_hachage[((fib2%N)+N)%N] = insertion(table_hachage[((fib2%N)+N)%N], fib2);
	}

	return 0;
}
