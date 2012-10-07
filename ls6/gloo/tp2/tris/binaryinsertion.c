     /* Binary insertion sort */
void BinInsertion(int * r, int lo, int up )
{
	int i, j, h, l;
	int tempr;
	// De 1 à n-1
	for ( i = lo + 1 ; i <= up; i++ ) {
		tempr = r[i]; // = r[1] à n-1

		l = lo;
		h = i;
		// On recherche (de manière dichotomique) où placer l'élément courant
		while( h-l > 1)
		{
			j = ( h + l ) / 2; // j = moyenne entre h et l
			if ( tempr <= r[j] ) // Si l'élément du milieu est > à l'élément courant
				h = j; 
			else 
				l = j;
		}
		// Si i > h alors on déplace de 1 vers la droite les éléments indice h à indice i
		for ( j = i ; j > h ; j-- ) 
			r[j] = r[j-1];
		r[h] = tempr;
	}
}
