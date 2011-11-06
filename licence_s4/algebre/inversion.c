#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

// À finir !!!
matrice_s * inversion_gauss_jordan(matrice_s * m)
{
	matrice_s * inverse;
	inverse = create_matrix(m->nbl, m->nbc);

	return inverse;
}
matrice_s * inversion_cofacteurs(matrice_s * m)
{
	matrice_s * inverse;
	inverse = create_matrix(m->nbl, m->nbc);

	return inverse;
}
