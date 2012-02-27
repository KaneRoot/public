#include "base.h"
#include "determinant.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrice_s * comatrice(matrice_s * m)
{
	matrice_s * co = create_matrix(m->nbl,m->nbc);
	int i, j;
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0; j < m->nbc ; j++)
			co->matrice[i][j] = determinant_i_j(m,i,j);
	return co;	
}
