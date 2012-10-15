#include <stdlib.h>



void Fusionner(int * A, int p, int q, int r)
{
  int i, j, k;
  int C[r+1];
  //  C = malloc((r-p+1)*sizeof(int));

  i = p;
  j = q+1;
  k = 1;

  while ((i <= q) && (j <= r))
    {
      if (A[i] < A[j])
	{ 
	  C[k] = A[i];
	  i = i+1;
	}
      else
	{
	  C[k] = A[j];
	  j = j+1;
	}
      k = k + 1;
    }

  while (i <= q)
    {
      C[k] = A[i];
      i = i+1;
      k = k + 1;
    }

  while (j <= r) 
    {
      C[k] = A[j];
      j = j+1;
      k = k + 1;
    }

  for(k = 1; k <=r-p+1; k++) A[p+k-1] = C[k];

  //  free(C);
}


void TriFusion(int * A, int p, int r)
{
  int q;

  if (p < r)
    {
      q = (p+r)/2;
      TriFusion(A, p, q);
      TriFusion(A, q+1, r);
      Fusionner(A, p, q, r);
    }
}

