#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "determinant.h"
#include "comatrice.h"
#include "calculs_base.h"
#include "inversion.h"
#include "gauss-jordan.h"

matrice_s * inversion_gauss_jordan(matrice_s * m1)
{
	int i, j, l_pivot = 0, c_pivot = 0;
	float coeff;
	matrice_s * inverse, * m;
	inverse = matrice_identitee(m1->nbc);
	m = dupliquer_matrice(m1);

	for(i = 0 ; i < m->nbl ; i++)
	{
		if((l_pivot = recherche_ligne_pivot_suivant(m, i, &c_pivot)) >= 0)
		{
			if(i != l_pivot)
			{
				inversion_lignes(m, i, l_pivot);
				inversion_lignes(inverse, i, l_pivot);
			}

			// multiplication ligne pivot par 1/pivot
			coeff = 1/m->matrice[l_pivot][c_pivot];
			for(j = 0 ; j < m->nbc ; j++)
				m->matrice[l_pivot][j] *= coeff;
			for(j = 0 ; j < m->nbc ; j++)
				inverse->matrice[l_pivot][j] *= coeff;

			for(j = 0 ; j < m->nbl ; j++)
			{
				if(j != i && m->matrice[j][c_pivot] != 0)
				{
					coeff = - ( m->matrice[j][c_pivot] / m->matrice[i][c_pivot] );
					addition_lignes(m, i, j, coeff);
					addition_lignes(inverse, i, j, coeff);
				}
			}
			c_pivot++;
		}
	}

	matrice_s * identitee = matrice_identitee(m->nbl);
	if(identiques(identitee, m) != 0)
	{
		free_matrix(identitee);
		free_matrix(m);
		free_matrix(inverse);
		return (matrice_s *) NULL;
	}

	free_matrix(identitee);
	free_matrix(m);

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
	
	printf("DETERMINANT : %f \n",det);

	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			tmp->matrice[i][j] /= det;

	printf("COMATRICE: \n");
	display_matrix(co);
	printf("TRANSPOSÉE COMATRICE/DET\n");
	display_matrix(tmp);

	free_matrix(co);
	return tmp;
}
