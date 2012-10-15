// Corrigé
void TriMax(int * A, int n)
{
	int m,r,t;
	int i, j;

	for( i = n-1 ; i > 0 ; i--)
	{
		for( j = 0, m = A[i], r = i ; j <= i ; j++)
		{
			if(A[j] > m)
			{
				m = A[j];
				r = j;
			}
		}
		t = A[r];
		A[r] = A[i];
		A[i] = t;
	}
}
