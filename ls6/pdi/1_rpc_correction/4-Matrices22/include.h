#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#define PROGNUM 0x20000135
#define VERSNUM 1
#define PROCNUM 1

// le type matrice22
struct matrice22
{
  float tab[2][2] ;
} ;

// renommage
typedef struct matrice22 matrice22 ;

// filtre xdr pour le type matrice
bool_t xdr_mat(XDR *xdrs, matrice22 * m) ;
// filtre xdr pour un couple de matrices
bool_t xdr_mat2(XDR *xdrs, matrice22 m[2]) ;

#endif /* __INCLUDE_H__ */
