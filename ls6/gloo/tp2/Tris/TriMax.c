void TriMax(int * A, int n)
{
  int m,r,t;
  int i, j;

  for(i=n-1; i>=1; i--)
    {
      for(j=0,m=0,r=0; j<=i; j++)
	if (A[j]>m)
	  {
	    m=A[j];
	    r=j;
	  }
      t=A[r];
      A[r]=A[i];
      A[i]=t;
    }
}
