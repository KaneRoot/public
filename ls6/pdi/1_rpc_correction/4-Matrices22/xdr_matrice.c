#include "include.h"

// filtre pour le type matrice
bool_t xdr_mat(XDR *xdrs, matrice22 *m)
{
  // on encode/décode le contenu de la matrice dans le flot
  return(xdr_float(xdrs, &m->tab[0][0]) && xdr_float(xdrs, &m->tab[0][1]) && 
         xdr_float(xdrs, &m->tab[1][0]) && xdr_float(xdrs, &m->tab[1][1])
  ) ;
}

// filtre pour un couple de matrice
bool_t xdr_mat2(XDR *xdrs, matrice22 m[2])
{
  // on appelle le filtre sur les deux matrices
  return (xdr_mat(xdrs, &(m[0])) && xdr_mat(xdrs, &(m[1]))) ;
}

