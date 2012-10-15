#include <stdlib.h>
#include <stdio.h>

void TriElim(int * A, int n)
{
	int m = A[0], valeur_max = A[0], indice_courant_valeur_max = 0, t;
	int i, j;

	// Recherche de la valeur_max
	for( i = 0 ; i < n ; i++)
		if (valeur_max < A[i])
		{
			valeur_max = A[i];
			indice_courant_valeur_max = i;
		}
	t = A[n-1];
	A[n-1] = A[indice_courant_valeur_max];
	A[indice_courant_valeur_max] = t;

	for( i = 1 ; i < n ; i++)
	{
		m = A[0];
		indice_courant_valeur_max = 0;
		for( j = 0 ; j < n-i ; j++)
		{
			if( A[j] >= m )
			{
				m = A[j];
				indice_courant_valeur_max = j;
			}
		}
		t = A[n-i-1];
		A[n-i-1] = A[indice_courant_valeur_max];
		A[indice_courant_valeur_max] = t;
		valeur_max = m;
	}
}

