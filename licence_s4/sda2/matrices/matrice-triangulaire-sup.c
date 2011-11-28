#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "matrice-triangulaire-sup.h"

#define N 5
#define VAL_DEFAUT 0

int truc(int n)
{	// plus simple : return n*(n+1)/2
	if(n == 0) return 0;
	return truc(n-1) + n;
}
Nat n()
{	
	return N;
}

matrice zero()
{
	int taille = truc(n());
	printf("On trouve une taille d'allocation de : %d \n", taille);
	matrice m = malloc(taille * sizeof(Rat));
	while(taille > 0)
	{
		taille--;
		m[taille] = VAL_DEFAUT;
	}

	return m;
}
int a(Nat i, Nat j)
{
	return n()*i-(((i-1)*i)/2) + j - i;
}
Rat elem(matrice m, Nat i, Nat j)
{
	if(j > i) return VAL_DEFAUT;
	return m[a(i, j)];
}

void modt(matrice m , Nat i, Nat j, Rat x)
{
	if(j > i) return;
	m[a(i, j)] = x;
}
matrice somme(matrice m1, matrice m2)
{
	matrice m = zero();
	int i, j;
	for(i = 0 ; i < n() ; i++)
		for(j = 0 ; j < n() ; j++)
			modt(m, i, j, elem(m1, i, j) + elem(m2, i, j));
	return m;
}
matrice prod(matrice m1, matrice m2)
{
	matrice m = zero();
	int i, j, k;
	Rat v = 0;

	for(i = 0 ; i < n() ; i++)
		for(j = 0 ; j < n() ; j++)
		{
			for(k = i ; k < j ; k++)
				v += elem(m1, i, k) x elem(m2, k,j);
			modt(m, i, j, v);
			v = 0;
		}
	return m;
}
matrice mult(matrice m, Rat x)
{
	matrice m1 = zero();
	int i, j;
	for(i = 0 ; i < n(); i++)
		for(j = 0 ; j < n() ; j++)
			modt(m1, i, j, elem(m,i,j) * x);
	return m1;
}
int main(int argc, char * argv[])
{
	matrice m = zero();
	modt(m, 1, 2, 15);

	return EXIT_SUCCESS;
}
