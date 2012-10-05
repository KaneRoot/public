#include "include.h"

int main (int argc, char **argv)
{
  char *host ;
  entiers2 res ;
  entiers2 donnees = {13 , 5} ;
  
  if (argc != 2)
  {
    printf("Usage : %s <MachineName>\n", argv[0]) ;
    exit(-1) ;
  }
  host = argv[1] ;
  
  // Appel à la procédure rpc distance
  ??? = callrpc(???) ; 
  if (??? ?= ???)
  {
    clnt_perror(???) ;
    return (-1) ;
  }

  printf("client res : %d/%d (q:%d r:%d)\n",donnees.x,donnees.y,res.x,res.y) ;

  return (0) ;
}
