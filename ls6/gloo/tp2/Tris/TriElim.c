#include <stdlib.h>
#include <stdio.h>

void TriElim(int * A, int n)
{
  int m=A[0],M=A[0],R=0,t;
  int i, j;

  for(i=0; i<n; i++)
    if (M<A[i])
      {
	M = A[i];
	R = i;
      }
  t = A[n-1];
  A[n-1] = A[R];
  A[R] = t;

  for(i=1; i<n-1; i++)
    {
      m=A[0];
      R=0;
      for(j=0; j<n; j++)
	{
	  if ((A[j]<M)&&(A[j]>m))
	    {
	      m=A[j];
	      R=j;
	    }
	}
      t = A[n-i-1];
      A[n-i-1] = A[R];
      A[R] = t;
      M=m;
    }
}

