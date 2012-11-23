#include "include.h"

// Filtre xdr pour la structure entiers2
bool_t xdr_entiers2(XDR *xdrs, entiers2 *e)
{
  return (
    xdr_int(xdrs, &(e->x)) &&
    xdr_int(xdrs, &(e->y))
  ) ;

}
