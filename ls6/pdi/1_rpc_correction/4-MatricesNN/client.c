#include "include.h"

int main (int argc, char *argv[])
{
  float  m1[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.} ;
  float m2[9] = {2., 0., 0., 0., 2., 0., 0., 0., 2.} ;
  matrice m[2] = {{(unsigned int)(3),m1}, {(unsigned int)(3),m2}} ; // matrices a multiplier
  matrice *pm[2] = {&(m[0]), &(m[1])} ;
  matrice *pres ; // pointeur sur la matrice resultat

  enum clnt_stat stat ;

  if (argc != 3)
  {
    fprintf(stderr, "Usage : %s <machine_serveur> <no procedure>\n", argv[0]) ;
    exit(1) ;
  }

  // call rpc procedure
  stat = callrpc(argv[1], PROGNUM, VERSNUM, atoi(argv[2]), (xdrproc_t)xdr_mat2, (char*)pm, (xdrproc_t)xdr_mat, (char *)&pres) ;
  if (stat != RPC_SUCCESS)
  {
    fprintf(stderr,"client, erreur dans callrpc : ") ;
    clnt_perrno(stat) ;
    fprintf(stderr,"\n") ;
    return 1 ;
  }

  fprintf(stdout,"client, le resultat : \n") ;
  affichemat(pres) ;
  
  xdr_freep(pres->tab) ; // libérer le tableau
  xdr_freep(pres) ; // libérer le pointeur global

  return 0 ;  
}

