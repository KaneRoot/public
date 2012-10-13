#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#define PROGNUM 0x20000115
#define VERSNUM 1
#define PROCNUM 1
#define TAILLE 2

// Structure contenant deux entiers
// Peut être utilisé pour la division (x/y) et pour le retour (x=quotient, y=reste).
typedef struct
{
	int m[TAILLE * TAILLE];
} matrix ;

typedef struct
{
	matrix a;
	matrix b;
} matrix_duo;

// Définition du filtre XDR pour la structure matrix
bool_t xdr_matrix(XDR *, matrix *) ;
bool_t xdr_matrix_duo(XDR *, matrix_duo*) ;
void afficher_matrice(matrix *m);

#endif // __INCLUDE_H__
