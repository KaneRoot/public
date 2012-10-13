#include "include.h"
int main (int argc, char **argv)
{
	char *host ;
	if (argc != 2)
	{
		printf("Usage : %s <MachineName>\n", argv[0]) ;
		exit(-1) ;
	}
	host = argv[1] ;

	int i,j;
	int stat;
	matrix res;
	matrix_duo argument;
	
	for(i = 0 ; i < TAILLE ; i++)
	{
		for(j = 0 ; j < TAILLE ; j++)
		{
			argument.a.m[i*TAILLE + j] = i + j % 3;
			argument.b.m[i*TAILLE + j] = i + j % 3 +1;
		}
		printf("\n");
	}
	printf("matrice a : "); afficher_matrice(&argument.a);
	printf("matrice b : "); afficher_matrice(&argument.b);


	// Appel à la procédure rpc distance
	stat = callrpc(host, PROGNUM, VERSNUM, PROCNUM,
			(xdrproc_t) xdr_matrix_duo, // procédure pour encoder le paramètre
			(char *) &argument, // pointeur vers la donnée (paramètre)
			(xdrproc_t) xdr_matrix, // procédure pour décoder le résultat
			(char *)&res); // adresse d'un pointeur vers le résultat

	if (stat != RPC_SUCCESS)
	{
		fprintf(stderr, "Echec de l'appel distant\n") ;
		clnt_perrno(stat) ;
		fprintf(stderr, "\n") ;
		return 1 ;
	}

	afficher_matrice(&res);
	return (0) ;
}
