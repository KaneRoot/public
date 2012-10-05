#include "include.h"

// procédure RPC de division de deux entiers
int * divise(xdr_entiers2 *e)
{ 
}

int main (void)
{
	// enregistrement de la procédure RPC
	bool_t stat = registerrpc(/* prognum */ PROGNUM,
			/* versnum */ VERSNUM,
			/* procnum */ PROCNUM,
			/* pointer on function */ divise,
			/* argument decoding */ (xdrproc_t)xdr_entiers2,
			/* function result encoding */ (xdrproc_t)xdr_entiers2) ;
	if (stat != RPC_SUCCESS)
	{
		fprintf(stderr, "Echec de l'appel distant\n") ;
		clnt_perrno(stat) ;
		fprintf(stderr, "\n") ;
		return 1 ;
	}

	svc_run() ; /* le serveur est en attente de clients eventuels */

	return(0) ; /* on y passe jamais ! */
}
