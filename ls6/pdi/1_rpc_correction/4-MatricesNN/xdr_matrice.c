#include "include.h"

matrice* malloc_mat(unsigned int n)
{
  matrice *mat ;
  mat = (matrice*) malloc (sizeof(matrice)) ;

  mat->n = n ;
  mat->tab = (float*) malloc (n*n*sizeof(float)) ;

  return mat ;
}

void affichemat(matrice *m)
{
  unsigned int i,j ;
  float *tab ;
  tab = m->tab ;
  
  fprintf(stdout,"Matrice de taille %u :\n",m->n) ;
  
  for (i = 0 ; i < m->n ; ++i)
  {
    for (j = 0 ; j < m->n ; ++j)
      fprintf(stdout, "%f ", *(tab++)) ;
    fprintf(stdout, "\n") ;
  }
}

void xdr_freep(void *p)
{
  fprintf(stdout, "Zone désallouée : %x\n", (unsigned)p) ;
  free(p) ;
}

// filtre pour le type matrice
bool_t xdr_mat(XDR *xdrs, matrice **m)
{
  unsigned int i, j, n ;
  float *c ;
  matrice *mat ;

  switch (xdrs->x_op) {                                                                 
    case XDR_ENCODE : fprintf(stderr,"xdr_mat  : ENCODE(%d)\n", xdrs->x_op) ;   break ; 
    case XDR_DECODE : fprintf(stderr,"xdr_mat  : DECODE(%d)\n", xdrs->x_op) ;   break ; 
    case XDR_FREE :   fprintf(stderr,"xdr_mat  : FREE(%d)\n", xdrs->x_op) ;     break ; 
    default :         fprintf(stderr,"xdr_mat  : default(%d)\n", xdrs->x_op) ;  break ; 
  }

  // encodage => encoder n
  if (xdrs->x_op == XDR_ENCODE)
  {
    mat = *m ;
    n = mat->n ;
    if (!xdr_u_int(xdrs, &n))
      return FALSE ;
  }
  else
  // décodage => décoder n et allouer la matrice
  if (xdrs->x_op == XDR_DECODE)
  {
    if (!xdr_u_int(xdrs, &n))
      return FALSE ;
    mat = malloc_mat(n) ;
    *m = mat ;
  }

  c = mat->tab ;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      if (!xdr_float(xdrs, c++))
        return FALSE ;

  return TRUE ;
}

// filtre pour un couple de matrice
bool_t xdr_mat2(XDR *xdrs, matrice **m2)
{
  matrice *pm0 = NULL ;
  matrice *pm1 = NULL ;

  switch (xdrs->x_op) {
    case XDR_ENCODE : // encode ==> encode both matrices
      fprintf(stderr,"xdr_mat2 : ENCODE(%d) pointeur %x\n",xdrs->x_op,(unsigned)m2) ;
      pm0 = m2[0] ;
      if (!xdr_mat(xdrs,&pm0)) return FALSE ;
      pm1 = m2[1] ;
      if (!xdr_mat(xdrs,&pm1)) return FALSE ;
      break ;
    case XDR_DECODE : // decode ==> decode both matrices (allocation done in subroutine)
      fprintf(stderr,"xdr_mat2 : DECODE(%d) pointeur %x\n",xdrs->x_op,(unsigned)m2) ;
      if (!xdr_mat(xdrs,&pm0)) return FALSE ;
      m2[0] = pm0 ;
      if (!xdr_mat(xdrs,&pm1)) return FALSE ;
      m2[1] = pm1 ;
      break ;
    case XDR_FREE : // free => free the pointer of each matrix
      fprintf(stderr,"xdr_mat2 : FREE(%d) pointeur %x\n",xdrs->x_op,(unsigned)m2) ;
      xdr_freep(m2[0]->tab) ;
      xdr_freep(m2[0]) ;
      xdr_freep(m2[1]->tab) ;
      xdr_freep(m2[1]) ;
      break ;
  }

  return TRUE ;
}
