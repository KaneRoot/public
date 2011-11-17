#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "determinant.h"
#include "comatrice.h"
#include "calculs_base.h"

// TODO
matrice_s * inversion_gauss_jordan(matrice_s * m)
{
	matrice_s * inverse;
	inverse = create_matrix(m->nbl, m->nbc);

	return inverse;
}
// (transposée de la comatrice) / déterminant
matrice_s * inversion_comatrices(matrice_s * m)
{
	int i, j;
	float det = det_nxn(m);
	matrice_s * co;
	matrice_s * tmp;
	if(det == 0.0)
		return (matrice_s *) NULL;

	co = comatrice(m);
	tmp = transposee_matrix(co);
	
	free_matrix(co);

	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			tmp->matrice[i][j] /= det;

	return tmp;
}
