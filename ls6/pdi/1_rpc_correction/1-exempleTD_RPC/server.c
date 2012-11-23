#include <stdio.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
// Remarque : malgre l'inclusion des librairies RPC, un warning de non declaration du prototype de registrrpc est declanche a la compilation.

#define PROGNUM 0x20000100
#define VERSNUM 1
#define PROCNUM 1

int * proc_dist(int *n)
{ 
  static int res = 1 ;
  printf("server: variable n (debut) : %d,\n",*n) ;
  res = (*n) + 1 ;
  *n = *n + 1 ;
  printf("server: variable n (fin) : %d,\n",*n) ;
  printf("server: variable res : %d\n",res) ;
  return &res ;
}

int main (void)
{
  registerrpc(/* prognum */ PROGNUM,
	     /* versnum */ VERSNUM,
	     /* procnum */ PROCNUM,
	     /* pointer on function */ proc_dist,
	     /* argument decoding */ (xdrproc_t)xdr_int,
	     /* function result encoding */ (xdrproc_t)xdr_int) ;

  svc_run() ; /* server ready for clients */

  return 0;
}


