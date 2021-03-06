#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "calculs_base.h"
#include "pivot-gauss.h"


int pivot_gauss_double_matrice(matrice_s * m1, matrice_s * m2)
{
	int i, j, booleen , l_pivot = 0, c_pivot = 0, retour = 0;
	float coeff;
	matrice_s * m, *identitee;
	m = dupliquer_matrice(m1); // Pour ne pas modifier directement la matrice m1

	for(i = 0 ; i < m->nbl ; i++)
	{
		if((l_pivot = recherche_ligne_pivot_suivant(m, i, &c_pivot)) >= 0)
		{
			if(i != l_pivot)
			{
				inversion_lignes(m, i, l_pivot);
				inversion_lignes(m2, i, l_pivot);
			}

			l_pivot = i;
			// multiplication ligne pivot par 1/pivot
			coeff = 1/m->matrice[l_pivot][c_pivot];
			for(j = 0 ; j < m->nbc ; j++)
				m->matrice[l_pivot][j] *= coeff;
			for(j = 0 ; j < m2->nbc ; j++)
				m2->matrice[l_pivot][j] *= coeff;

			for(j = 0 ; j < m->nbl ; j++)
			{
				if(j != i && m->matrice[j][c_pivot] != 0)
				{
					coeff = - ( m->matrice[j][c_pivot] / m->matrice[i][c_pivot] );
					addition_lignes(m, i, j, coeff);
					addition_lignes(m2, i, j, coeff);
				}
			}
			c_pivot++;
		}
	}

	// On vérifie qu'une fois qu'on a terminé m1 = matrice identité
	// Sinon : erreur dans le pivot
	identitee = matrice_identitee(m->nbl);
	if(identiques(identitee, m) == 0)
		retour = 0;
	else
	{
		retour = -1;
		for(i = 0 ; booleen == 0 && i < m->nbl ; i++)
		{
			booleen = 0;
			for(j = 0 ; booleen == 0 && j < m->nbc ; j++)
				if(m->matrice[i][j] != 0)
					booleen = 1;
			// Nous avons une ligne vide sur la matrice gauche => à droite ça DOIT l'être aussi
			for(j = 0 ; booleen == 0 && j < m2->nbc ; j++)
				if(m2->matrice[i][j] != 0)
					booleen = -1;

			if(booleen == 0)
				retour = i;
		}
	}

	free_matrix(m);
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
