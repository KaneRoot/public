#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"

float calcul_determinant_nxn(matrice_s *m)
{
	if(m == NULL || m->nbc != m->nbl)
		return -1.0;

	if(m->nbl == 2 && m->nbc == 2)
		return (m->matrice[0][0] * m->matrice[1][1]) - (m->matrice[1][0] * m->matrice[0][1]);

	float somme = 0;
	int i, j,k,l,tmpk = 0, tmpl = 0, lignes;
	matrice_s * tmp;

	lignes = (m->nbl > 3) ? 1 : m->nbl;

	for(i = 0 ; i < lignes ; i++)
	{
		for(j = 0 ; j < m->nbc ; j++)
		{
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
			tmpk = 0;
			//display_matrix(tmp);
			//if(m->nbl == 3) printf("\t");
			if((i % 2) == 0)
				somme += (m->matrice[i][j] * calcul_determinant_nxn(tmp));
			else
				somme -= (m->matrice[i][j] * calcul_determinant_nxn(tmp));

			free_matrix(tmp);
		}
	}
	return somme;
}
