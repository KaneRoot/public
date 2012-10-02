void TriMax(int * A, int n)
{
	int m,r,t;
	int i, j;

	for( i = n-1 ; i > 0 ; i--)
	{
		// ici on cherche l'élément le plus grand
		// r : indice élément plus grand entre les indices 0 et i
		for( j = 0 , m = A[i] , r = 0 ; j <= i ; j++)
		{
			if(A[j] > m)
			{
				m = A[j];
				r = j;
			}
		}

		// échange élement numéro r avec i
		t = A[r];
		A[r] = A[i];
		A[i] = t;
	}
}
