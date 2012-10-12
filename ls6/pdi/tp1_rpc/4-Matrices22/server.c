#include "include.h"

// procédure RPC de division de deux entiers
matrix * addition(matrix_duo *d)
{ 
	static matrix m;
	int i, j;

	printf("Reçu a : "); afficher_matrice(&d->a);
	printf("Reçu b : "); afficher_matrice(&d->b);

	for(i = 0 ; i < TAILLE ; i++)
		for(j = 0 ; j < TAILLE ; j++)
			m.m[i][j] = d->a.m[i][j] + d->b.m[i][j];

	return (&m);
}

int main (void)
{
	// enregistrement de la procédure RPC
	bool_t stat = registerrpc(/* prognum */ PROGNUM,
			/* versnum */ VERSNUM,
			/* procnum */ PROCNUM,
			/* pointer on function */ addition,
			/* argument decoding */ (xdrproc_t)xdr_matrix_duo,
			/* function result encoding */ (xdrproc_t)xdr_matrix) ;

	if (stat != RPC_SUCCESS)
	{
		fprintf(stderr, "echec creation fonction addition RPC") ;
		clnt_perrno(stat) ;
		fprintf(stderr, "\n") ;
		return 1 ;
	}

	svc_run() ; /* le serveur est en attente de clients eventuels */

	return(0) ; /* on y passe jamais ! */
}
