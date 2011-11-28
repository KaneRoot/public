#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "matrice-triangulaire-sup.h"

#define N 3
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
	if(i > j) return VAL_DEFAUT;
	return m[a(i, j)];
}

void modt(matrice m , Nat i, Nat j, Rat x)
{
	if(i > j) return;
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
				v += elem(m1, i, k) * elem(m2, k,j);
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
void affichage_matrice(matrice m)
{
	int i, j;
	for(i = 0 ; i < n() ; i++)
		for(j = 0 ; j < n() ; j++)
			printf("Matrice %d %d = %lf\n", i, j, elem(m, i, j));
}
int main(int argc, char * argv[])
{
	matrice m = zero();
	modt(m, 1, 1, 15);
	modt(m, 0, 1, 12);
	affichage_matrice(m);
	
	matrice m1, m2;
	m1 = zero();
	m2 = zero();
	
	int i, j;
	for(i = 0 ; i < n() ; i++)
		for(j = 0 ; j < n() ; j++)
			modt(m1, i, j, i+j);
	printf("Matrice m1\n");
	affichage_matrice(m1);
	for(i = 0 ; i < n() ; i++)
		for(j = 0 ; j < n() ; j++)
			modt(m2, i, j, i+j);
	printf("Matrice m2\n");
	affichage_matrice(m2);

	printf("Matrice m3\n");
	matrice m3 = mult(m1, 5);

	affichage_matrice(m3);
	matrice m4 = prod(m3, m1);
	printf("Matrice m4\n");
	affichage_matrice(m4);
	return EXIT_SUCCESS;
}
