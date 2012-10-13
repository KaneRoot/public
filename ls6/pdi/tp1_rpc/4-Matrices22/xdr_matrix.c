#include "include.h"

// Filtre xdr pour la structure matrix
bool_t xdr_matrix(XDR *xdrs, matrix *m)
{
	int i,j, res = 0;
	static int k = 0;
	static int l = 0;

	if(xdrs->x_op == XDR_DECODE && m == NULL)
	{
		printf("malloc matrix\n");
		m = malloc(sizeof(matrix));
	}
	switch(xdrs->x_op)
	{
		case XDR_ENCODE :
			k++;
			printf("encode k : %d",k);
			afficher_matrice(m);

			for(i = 0 ; i < TAILLE ; i++)
				for(j = 0 ; j < TAILLE && res == 0 ; j++)
					res = xdr_int(xdrs, &m->m[i* TAILLE + j]);

			break;
		case XDR_DECODE :
			l++;
			printf("decode l : %d",l);

			for(i = 0 ; i < TAILLE ; i++)
				for(j = 0 ; j < TAILLE && res == 0 ; j++)
					res = xdr_int(xdrs, &m->m[i* TAILLE + j]);
			afficher_matrice(m);
			break;

		default :
			break;
	}

	return res;
}
bool_t xdr_matrix_duo(XDR *xdrs, matrix_duo *d)
{
	if(xdrs->x_op == XDR_DECODE && d == NULL)
	{
		printf("malloc matrix_duo\n");
		d = malloc(sizeof(matrix_duo));
	}
	matrix * a = &d->a;
	matrix * b = &d->b;
	
//	return (xdr_matrix(xdrs, &a) && xdr_matrix(xdrs, &b));
	
	int res = 0;
	// xdrs->op donne le type de flot (encodage/décodage/libération)
	switch(xdrs->x_op)
	{
		case XDR_ENCODE :
			res = (xdr_matrix(xdrs, a) && xdr_matrix(xdrs, b));
			break;
		default :
			res = (xdr_matrix(xdrs, a) && xdr_matrix(xdrs, b));

			break;
	}

	return res;
}

void afficher_matrice(matrix *m)
{
	int i, j;
	printf("\n");
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0 ; j < TAILLE ; j++)
			printf(" %3d ", m->m[i*TAILLE + j]);
		printf("\n");
	}
	printf("\n");
}
