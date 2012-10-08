     /* Binary insertion sort */
void BinInsertion(int * r, int lo, int up )
{
	int i, j, h, l;
	int tempr;
	for ( i = lo + 1; i <= up ; i++ ) 
	{
		tempr = r[i];

		l = lo - 1;
		h = i;
		while ( h-l > 1 ) 
		{
			j = ( h + l ) / 2;
			if ( tempr <= r[j] ) 
				h = j; 
			else 
				l = j;
		}
		for ( j = i; j > h; j-- ) 
		{

			r[j] = r[j-1];
		}
		r[h] = tempr;
	}
}
