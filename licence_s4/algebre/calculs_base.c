#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"


matrice_s * add_matrix(matrice_s * m1, matrice_s * m2)
{
	if(m1->nbl != m2->nbl || m1->nbc != m2->nbc)
		return (matrice_s *) NULL;

	int i, j;
	matrice_s * somme = create_matrix(m1->nbl,m1->nbc);
	
	for(i = 0 ; i < m1->nbl ; i++)
		for(j = 0 ; j < m1->nbc ; j++)
			somme->matrice[i][j] = m1->matrice[i][j] + m2->matrice[i][j];
	return somme;
}
matrice_s * multiplication_matrices(matrice_s *m1, matrice_s *m2)
{
	int i, j, k;
	int somme;
	if(m1->nbc != m2->nbl)
		return (matrice_s *) NULL;

	matrice_s *m = create_matrix(m1->nbl, m2->nbc);

	for(i = 0 ; i < m1->nbl; i++)
	{
		for(j = 0 ; j < m2->nbc ; j++)
		{
			somme = 0;
			for(k = 0; k < m1->nbc ; k++)
				somme += (m1->matrice[i][k] * m2->matrice[k][j]);
			m->matrice[i][j] = somme;
		}
	}
	return m;
}
matrice_s * transposee_matrix(matrice_s *m)
{
	int i,j;
	matrice_s * t = create_matrix(m->nbc, m->nbl);
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			t->matrice[j][i] = m->matrice[i][j];
	return t;
}
// addition_lignes( matrice , ligne de départ , ligne à multiplier , coefficient multiplicateur)
matrice_s * addition_lignes(matrice_s * m, int l_depart, int l_a_mul, float coeff)
{
	int i;
	for(i = 0 ; i < m->nbc ; i++)
		m->matrice[l_a_mul][i] = m->matrice[l_a_mul][i] + coeff * m->matrice[l_depart][i];

	return m;
}

matrice_s * inversion_lignes(matrice_s * m , int l1, int l2)
{
	int i;
	matrice_s * mtmp = create_matrix(2, m->nbc);

	// On place dans la matrice temporaire les 2 lignes l1 et l2
	for(i = 0 ; i < m->nbc ; i++)
		mtmp->matrice[0][i] = m->matrice[l1][i];
	for(i = 0 ; i < m->nbc ; i++)
		mtmp->matrice[1][i] = m->matrice[l2][i];
	
	// On remplace les lignes l1 par l2 et inversement
	for(i = 0 ; i < m->nbc ; i++)
		m->matrice[l1][i] = mtmp->matrice[1][i];
	for(i = 0 ; i < m->nbc ; i++)
		m->matrice[l2][i] = mtmp->matrice[0][i];

	free_matrix(mtmp); // suppression de mtmp

	return m;
}

matrice_s * matrice_identitee(int taille)
{
	int i;
	matrice_s * m = create_matrix(taille, taille);
	for(i = 0 ; i < taille ; i++)
		m->matrice[i][i] = 1;

	return m;
}

matrice_s * dupliquer_matrice(matrice_s * m)
{
	int i, j;
	matrice_s * m2 = create_matrix(m->nbl, m->nbc);
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			m2->matrice[i][j] = m->matrice[i][j];
	return m2;
}
