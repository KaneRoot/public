#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#define PROGNUM 0x20001??? // 3 chiffres à définir librement
#define VERSNUM 1
#define PROCNUM 1

// Structure contenant deux entiers
// Peut être utilisé pour la division (x/y) et pour le retour (x=quotient, y=reste).
typedef struct
{
  int x ;
  int y ;
} entiers2 ;

// Définition du filtre XDR pour la structure entiers2
bool_t xdr_entiers2(XDR *, entiers2 *) ;

#endif // __INCLUDE_H__
