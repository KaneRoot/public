#include "tri.h"

int Partitionnement(int * A, int p, int r)
{
	int x, i, j, tmp;

	x = A[p];
	i = p-1;
	j = r+1;

	while(1)
	{
		do 
		{ 
			j--;
		}
		while(A[j] > x);

		do
		{
			i++;
		}
		while (A[i] < x);

		if (i < j)
		{
			tmp  = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
		else
		{
			return j;
		}
	}
}

void TriRapide(int * A, int p, int r)
{
	int q;

	if (p < r) 
	{
		q = Partitionnement(A, p, r);
		TriRapide(A, p, q);
		TriRapide(A, q+1, r);
	}
}
