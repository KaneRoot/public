#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#define PROGNUM 0x20000135
#define VERSNUM 1
#define PROCNUM 1

// le type matrice NxN
struct matrice
{
  unsigned int n ;
  float* tab ; // codée en 1D
} ;

// renommage
typedef struct matrice matrice ;

// fonction d'allocation mémoire pour une matrice
matrice* malloc_mat(unsigned int n) ;

// fonction d'affichage d'une matrice NxN
void affichemat(matrice *m) ;

// fonction de désallocation mémoire
void xdr_freep(void *p) ;

// filtre xdr pour le type matrice
bool_t xdr_mat(XDR *xdrs, matrice **m) ;
// filtre xdr pour un couple de matrices
bool_t xdr_mat2(XDR *xdrs, matrice **m2) ;

#endif /* __INCLUDE_H__ */
