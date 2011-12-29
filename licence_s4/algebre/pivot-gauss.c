#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "calculs_base.h"
#include "pivot-gauss.h"


int pivot_gauss_double_matrice(matrice_s * m1, matrice_s * m2)
{
	int i, j, l_pivot = 0, c_pivot = 0, retour = 0;
	float coeff;
	matrice_s * m;
	m = dupliquer_matrice(m1);

	for(i = 0 ; i < m->nbl ; i++)
	{
		if((l_pivot = recherche_ligne_pivot_suivant(m, i, &c_pivot)) >= 0)
		{
			if(i != l_pivot)
			{
				inversion_lignes(m, i, l_pivot);
				inversion_lignes(m2, i, l_pivot);
			}

			// multiplication ligne pivot par 1/pivot
			coeff = 1/m->matrice[l_pivot][c_pivot];
			for(j = 0 ; j < m->nbc ; j++)
				m->matrice[l_pivot][j] *= coeff;
			for(j = 0 ; j < m2->nbc ; j++)
				m2->matrice[l_pivot][j] *= coeff;

//	printf(" avant  m : \n");
//	display_matrix(m);
//	printf(" avant m2 : \n");
//	display_matrix(m2);
//	printf("\033[31m=========================================\033[00m\n");

			for(j = 0 ; j < m->nbl ; j++)
			{
				printf("Je suis arrivé jusque-là 2!\n");
				if(j != i && m->matrice[j][c_pivot] != 0)
				{
					coeff = - ( m->matrice[j][c_pivot] / m->matrice[i][c_pivot] );
					addition_lignes(m, i, j, coeff);
					addition_lignes(m2, i, j, coeff);
				}
				printf("Je suis arrivé jusque-là 3!\n");
			}
//	printf(" après  m : \n");
//	display_matrix(m);
//	printf(" après m2 : \n");
//	display_matrix(m2);
//	printf("\033[31m=========================================\033[00m\n");
			c_pivot++;
		}
	}

	matrice_s * identitee = matrice_identitee(m->nbl);
	if(identiques(identitee, m) == 0)
		retour = 0;
	else
		retour = 1;

	free_matrix(identitee);
	return retour;
}

// Recherche la ligne du prochain pivot, en partant d'une ligne et d'une colonne
// Retourne la ligne pivot ou -1 s'il n'y a pas 
int recherche_ligne_pivot_suivant(matrice_s * m, int l_depart, int * c_depart)
{
	int indice = -1,i, *j;

	for( j = c_depart ; indice == -1 && *j < m->nbc ; j[0]++)
		for(i = l_depart ; indice == -1 && i < m->nbl; i++)
			if(m->matrice[i][*j] != 0)
				indice = i;

	j[0]--;
	return indice;
}
