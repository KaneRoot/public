#include "include.h"

int main (int argc, char *argv[])
{
  char *host ;
  entiers2 res ;
  entiers2 donnees = {13 , 5} ;
  enum clnt_stat stat ;
  
  if (argc != 2)
  {
    printf("Usage : %s <MachineName>\n", argv[0]) ;
    exit(-1) ;
  }
  host = argv[1] ;
  
  // Appel à la procédure rpc distance
  stat = callrpc(/* host */ host, /* prognum */ PROGNUM,
                 /* versnum */ VERSNUM, /* procnum */ PROCNUM,
                 /* encodage argument */ (xdrproc_t) xdr_entiers2,
                 /* argument */ (char *)&donnees,
                 /* decodage retour */ (xdrproc_t)xdr_entiers2,
                 /* retour de la fonction distante */(char *)&res) ;

  if (stat != RPC_SUCCESS)
  { 
    fprintf(stderr, "Echec de l'appel distant\n") ;
    clnt_perrno(stat) ;
    fprintf(stderr, "\n") ;
    return 1 ;
  }

  printf("client res : %d/%d (q:%d r:%d)\n", donnees.x, donnees.y, res.x, res.y) ;
  return 0 ;
}
