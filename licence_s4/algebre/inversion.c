#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "determinant.h"
#include "comatrice.h"
#include "calculs_base.h"
#include "inversion.h"
#include "pivot-gauss.h"

matrice_s * inversion_gauss_jordan(matrice_s * m1)
{
	matrice_s * inverse = matrice_identitee(m1->nbl);
	if(0 > pivot_gauss_double_matrice(m1, inverse))
	{
		free_matrix(inverse);
		inverse = NULL;
	}
	return inverse;
}
// (transposée de la comatrice) / déterminant
matrice_s * inversion_comatrices(matrice_s * m)
{
	int i, j;
	matrice_s *co, *tmp;
	float det = det_nxn(m);

	if(det == 0.0)
		return (matrice_s *) NULL;

	co = comatrice(m);
	tmp = transposee_matrix(co);

	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			tmp->matrice[i][j] /= det;

	free_matrix(co);
	return tmp;
}
