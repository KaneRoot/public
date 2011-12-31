#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "calculs_base.h"


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
void pmatrice_addition_lignes(pmatrice_s * pm, int l_depart, int l_a_mul, float coeff)
{
	int i;
	polynome_s ** ptmp2 = malloc(sizeof(polynome_s*) * pm->nbc);
	polynome_s ** ptmp3 = malloc(sizeof(polynome_s*) * pm->nbc);
	for(i = 0 ; i < pm->nbc ; i++)
	{
		ptmp2[i] = multiplication_polynome_par_reel(pm->matrice[l_a_mul][i], coeff);
		ptmp3[i] = addition_polynomes_prem(ptmp2[i], pm->matrice[l_depart][i]);
		free_polynome(pm->matrice[l_depart][i]);
		pm->matrice[l_depart][i] = ptmp3[i];
	}

	for(i = 0 ; i < pm->nbc ; i++)
		free_polynome(ptmp2[i]);

	free(ptmp2);
	free(ptmp3);
}
polynome_s * addition_polynomes_prem(polynome_s * p1, polynome_s * p2)
{
	return creation_poly_prem(p1->matrice[0][1] + p2->matrice[0][1], p1->matrice[0][0] + p2->matrice[0][0]);
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
void pmatrice_inversion_lignes(pmatrice_s * pm, int ligne1, int ligne2)
{
	polynome_s ** p = malloc(sizeof(polynome_s) * pm->nbc);
	int i;

	for(i = 0 ; i < pm->nbc ; i++)
		p[i] = pm->matrice[ligne1][i];

	for( i = 0 ; i < pm->nbl ; i++)
		pm->matrice[ligne1][i] = pm->matrice[ligne2][i];

	for(i = 0 ; i < pm->nbl ; i++)
		pm->matrice[ligne2][i] = p[i];

	free(p);
}
void pmatrice_inversion_colonnes(pmatrice_s * pm, int col1, int col2)
{
	polynome_s ** p = malloc(sizeof(polynome_s) * pm->nbl);
	int i;

	for(i = 0 ; i < pm->nbl ; i++)
		p[i] = pm->matrice[i][col1];

	for( i = 0 ; i < pm->nbl ; i++)
		pm->matrice[i][col1] = pm->matrice[i][col2];

	for(i = 0 ; i < pm->nbl ; i++)
		pm->matrice[i][col2] = p[i];

	free(p);
}
// Multiplication de 2 polynômes de premier degré
polynome_s * multiplication_polynomes_prem(polynome_s * p1, polynome_s * p2)
{
	polynome_s * resultat;

	resultat = creation_poly_sec(
			p1->matrice[0][1] * p2->matrice[0][1],
			p1->matrice[0][0] * p2->matrice[0][1] + p1->matrice[0][1] * p2->matrice[0][0],
			p1->matrice[0][0] * p2->matrice[0][0]);

	return resultat;
}
// Soustraction de polynômes de second degré
polynome_s * soustraction_polynomes_sec(polynome_s * p1, polynome_s * p2)
{
	// Certes, ce n'est pas fait dans la finesse. Je manque de temps.
	return creation_poly_sec(p1->matrice[0][2] - p2->matrice[0][2], p1->matrice[0][1] - p2->matrice[0][1] , p1->matrice[0][0] - p2->matrice[0][0]);
}
// On cherche à savoir si le polynôme est vide
// 0 si vide, 1 sinon
int polynome_vide(polynome_s * p)
{
	int b = 0 ,i;
	for(i = 0 ; b == 0 && i < p->nbc ; i++)
		if( 0 != p->matrice[0][i] )
			b = 1;

	return b;
}
// Vérifie si 2 matrices sont identiques
int identiques(matrice_s * m1, matrice_s *m2)
{
	int i, j;
	int b = 0;
	if( m1->nbc != m2->nbc || m1->nbl != m2->nbl)
		b = 1;
	for(i = 0 ; i < m1->nbl && b == 0 ; i++)
		for(j = 0 ; j < m1->nbc && b == 0 ; j++)
			if(m1->matrice[i][j] != m2->matrice[i][j])
				b = 1;
	return b;
}
// Multiplication d'un polynôme par un réel
polynome_s * multiplication_polynome_par_reel(polynome_s * p, float reel)
{
	int i;
//	printf("Polynôme en entrée : \n");
//	display_polynome(p);
	polynome_s * resultat = dupliquer_polynome(p);
	for(i = 0 ; i < resultat->nbc ; i++)
		resultat->matrice[0][i] = resultat->matrice[0][i] * reel;

//	printf("Polynôme en sortie : \n");
//	display_polynome(resultat);

	return resultat;
}
// Duplication d'un polynôme
polynome_s * dupliquer_polynome(polynome_s * p)
{
	return (polynome_s *) dupliquer_matrice((matrice_s *) p);
}
