#include "include.h"

matrice** multiplier(matrice **mat2)
{
  unsigned int c = 0, i, j, k ;
  unsigned int n = mat2[0]->n ;
  static matrice *mres = NULL ;

  if (mres != NULL) // possible car static
  {
    xdr_freep(mres->tab) ;
    xdr_freep(mres) ;
  }
  mres = malloc_mat(n) ;

  fprintf(stdout,"MULTIPLICATION\n") ;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
    {
      mres->tab[c] = 0 ;
      for (k = 0; k < n; ++k)
        mres->tab[c] += mat2[0]->tab[i*n+k] * mat2[1]->tab[k*n+j] ;
      ++c ;
    }

  return &mres ;
}

matrice ** additioner(matrice **mat2)
{
  unsigned int c = 0, i, j ;
  unsigned int n = mat2[0]->n ;
  static matrice *mres = NULL ;

  if (mres != NULL)
  {
    xdr_freep(mres->tab) ;
    xdr_freep(mres) ;
  }

  mres = malloc_mat(n) ;

  fprintf(stdout,"ADDITION\n") ;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
    {
      mres->tab[c] = mat2[0]->tab[c] + mat2[1]->tab[c] ;
      ++c ;
    }

  sleep(7) ;

  return &mres ;
}

int main (void)
{
  registerrpc(PROGNUM,VERSNUM,1,multiplier,xdr_mat2,xdr_mat) ;
  registerrpc(PROGNUM,VERSNUM,2,additioner,xdr_mat2,xdr_mat) ;

  svc_run() ;

  return(0) ;
}

