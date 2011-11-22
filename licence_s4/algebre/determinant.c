#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "determinant.h"

#define ERROR_MATRICE_NULLE 1e20
#define ERROR_MATRICE_NON_CARRE 1e21

float determinant_i_j(matrice_s *m, int i, int j)
{
	if(m == NULL)			return ERROR_MATRICE_NULLE;
	if(m->nbc != m->nbl)	return ERROR_MATRICE_NON_CARRE;

	if(m->nbl == 2 && m->nbc == 2)
		return (m->matrice[0][0] * m->matrice[1][1]) - (m->matrice[1][0] * m->matrice[0][1]);

	float retour;
	int k,l,tmpk = 0, tmpl = 0;
	matrice_s * tmp;

	tmp = create_matrix((m->nbl-1), (m->nbc -1));
	for(k = 0 ; k < m->nbl ; k++)
	{
		if(k == i)
		{
			k++;
			tmpk++;
		}
		if(k >= m->nbl) break;
		for(l = 0 ; l < m->nbc ; l++)
		{
			if(l == j)
			{
				l++;
				tmpl++;
			}
			if(l >= m->nbc) break;
			tmp->matrice[k - tmpk][l - tmpl] = m->matrice[k][l];
		}
		tmpl = 0;
	}

	retour = (m->matrice[i][j] * powf((float)-1,(float)i+j) * det_nxn(tmp));

	free_matrix(tmp);
	return retour;
}
float det_nxn(matrice_s * m)
{
	float retour = 0;
	int i;
	if(m->nbl == 2)
		return determinant_i_j(m,0,0);
	for(i = 0 ; i < m->nbc ; i++)
	{
		//printf("Retour : %f \n", determinant_i_j(m,0,i));
		retour += determinant_i_j(m, 0, i);
	}

	return retour;
}
