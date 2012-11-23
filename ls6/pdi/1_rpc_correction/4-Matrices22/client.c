#include "include.h"

int main (int argc, char *argv[])
{
  char *host ;
  int procnum ;

  matrice22 mat[2] ;
  matrice22 res ;
  
  enum clnt_stat stat ;

  if (argc != 3)
  {
    printf("Usage : %s <machine_serveur> <no de procedure>\n",argv[0]) ;
    exit(1) ;
  }

  host = argv[1] ;

  (mat[0]).tab[0][0] = 1 ;
  (mat[0]).tab[0][1] = 2 ;
  (mat[0]).tab[1][0] = 3 ;
  (mat[0]).tab[1][1] = 4 ;
  
  (mat[1]).tab[0][0] = 1 ;
  (mat[1]).tab[0][1] = 0 ;
  (mat[1]).tab[1][0] = 0 ;
  (mat[1]).tab[1][1] = 2 ;

  procnum = atoi(argv[2]) ;
  
  // si numéro inconne : defaut = 1
  if ((procnum != 1) && (procnum != 2))
    procnum = 1;
  
  // appel RPC
  stat = callrpc(host,PROGNUM,VERSNUM,procnum, (xdrproc_t)xdr_mat2, (char*)&mat, (xdrproc_t)xdr_mat, (char *)&res) ;
  
  if (stat != RPC_SUCCESS)
  { 
    fprintf(stderr, "Echec de l'appel distant\n") ;
    clnt_perrno(stat) ;
    fprintf(stderr, "\n") ;
    return 1 ;
  }

  printf("client, le resultat : \n%f %f \n%f %f\n", res.tab[0][0], res.tab[0][1], res.tab[1][0], res.tab[1][1]) ;
  return 0 ;  
}

