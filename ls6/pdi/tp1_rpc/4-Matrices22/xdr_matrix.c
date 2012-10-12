#include "include.h"

// Filtre xdr pour la structure matrix
bool_t xdr_matrix(XDR *xdrs, matrix **m)
{
	int i,j;
	static int k = 0;
	int res = 0;
	// xdrs->op donne le type de flot (encodage/décodage/libération)
	// ce switch n'a pas vraiment d'intérêt
	switch(xdrs->x_op)
	{
		case XDR_ENCODE :
			k++;
			printf("k : %d",k);
			afficher_matrice(*m);
			
			for(i = 0 ; i < TAILLE ; i++)
				for(j = 0 ; j < TAILLE && res == 0 ; j++)
					res = xdr_int(xdrs, &(*m)->m[i][j]);

			break;
		default :
			break;
	}

	return res;
}
bool_t xdr_matrix_duo(XDR *xdrs, matrix_duo *d)
{
	matrix * a = &d->a;
	matrix * b = &d->b;

	return (xdr_matrix(xdrs, &a) && xdr_matrix(xdrs, &b));
}

void afficher_matrice(matrix *m)
{
	int i, j;
	printf("\n");
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0 ; j < TAILLE ; j++)
			printf(" %3d ", m->m[i][j]);
		printf("\n");
	}
	printf("\n");
}
