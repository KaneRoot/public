#include <stdio.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>


#define PROGNUM 0x20000100
#define VERSNUM 1
#define PROCNUM 1



int main (int argc, char **argv)
{
  int res = 0,  n=0x41424344 ; 
  char *host ;
  enum clnt_stat stat ;

  if (argc != 2)
  {
    printf("Usage: %s server_location\n",argv[0]) ;
    exit(0) ;
  }
  
  host = argv[1] ;

  printf("client: variable n (begin) : %d %s,\n",n,(char *)&n) ;

  stat = callrpc(/* host */ host,
		 /* prognum */ PROGNUM,
		 /* versnum */ VERSNUM,
		 /* procnum */ PROCNUM,
		 /* argument encoding filter */ (xdrproc_t) xdr_int,
		 /* argument */ (char *)&n,
		 /* return value decoding filter */ (xdrproc_t)xdr_int,
		 /* retour value */(char *)&res) ;

  if (stat != RPC_SUCCESS)
  {
    fprintf(stderr, "Echec de l'appel distant\n") ;
    clnt_perrno(stat) ;
    fprintf(stderr, "\n") ;
    return 1 ;
  }

  printf("client: variable n (end) : %d,\n",n) ;
  printf("client: variable res : %d\n",res) ;
  
  return 0 ;
}



