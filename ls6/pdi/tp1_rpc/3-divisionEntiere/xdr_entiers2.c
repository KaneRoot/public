#include "include.h"

// Filtre xdr pour la structure entiers2
bool_t xdr_entiers2(XDR *xdrs, entiers2 *e)
{
	int res = 0;
	// xdrs->op donne le type de flot (encodage/décodage/libération)
	// ce switch n'a pas vraiment d'intérêt
	switch(xdrs->x_op)
	{
		case XDR_ENCODE : res = (xdr_int(xdrs,&e->x) && xdr_int(xdrs,&e->y));
		case XDR_DECODE : res = (xdr_int(xdrs,&e->x) && xdr_int(xdrs,&e->y));
		default : res = (xdr_int(xdrs,&e->x) && xdr_int(xdrs,&e->y));
	}
	return res;
}
