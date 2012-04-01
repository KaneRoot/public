#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mesfonctions.h"


// Affichage d'une pmatrice
void display_pmatrix(pmatrice_s * pm)
{
	if(pm == NULL)
	{
		printf("\033[31mLa pmatrice n'existe pas \033[32m-- calcul impossible ?\033[00m\n");
		return ;
	}
	int i, j;

	printf( "  " );
	for ( i = 0 ; i < pm->nbc ; i++ ) 
		printf( "          %4d  ", i ); 
	printf( "\n     " );
	for ( i = 0 ; i < pm->nbc ; i++ ) 
		printf( "-----------------" ); 
	printf( "\n" );

	for ( i = 0 ; i < pm->nbl ; i++ ) 
	{
		printf( " %2d |", i );	
		for ( j = 0 ; j < pm->nbc ; j++ )
		{
			display_polynome_core(pm->matrice[i][j]);
			printf(" | ");
		}

		printf( "\n" );
	}
	printf( "\n" );
}
// Affichage (joli) d'un polynôme
void display_polynome(polynome_s * p)
{
	if(p == NULL)
	{
		printf("\033[31mPas de polynôme ! \033[00m\n");
		return ;
	}
	printf("\033[32mPolynôme : [[ \033[00m ");
	display_polynome_core(p);
	printf("\033[32m ]] \033[00m \n");
}
// Affichage (joli) d'une matrice
void display_matrix(matrice_s * m) 
{
	if(m == NULL)
	{
		printf("\033[31mLa matrice n'existe pas \033[32m-- calcul impossible ?\033[00m\n");
		return ;
	}
	int i, j;

	printf( "    " );
	for ( i = 0 ; i < m->nbc ; i++ ) 
		printf( " %4d", i ); 
	printf( "\n     " );
	for ( i = 0 ; i < m->nbc ; i++ ) 
		printf( "-----" ); 
	printf( "\n" );

	for ( i = 0 ; i < m->nbl ; i++ ) 
	{
		printf( " %2d |", i );	
		for ( j = 0 ; j < m->nbc ; j++ )
			printf( " %2.2f", m->matrice[i][j] );

		printf( "\n" );
	}
	printf( "\n" );
}
// Créer une matrice vide
matrice_s * create_matrix(int nbl, int nbc)
{
	int i,j;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	for(i = 0 ; i < nbl ; i++)
		t[i] = (float*)malloc(nbc * sizeof(float));

	matrice_s * m = malloc(sizeof(matrice_s));
	m->matrice = t;
	m->nbl = nbl;
	m->nbc = nbc;
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			m->matrice[i][j] = 0;
	return m;
}
// Suppression d'une matrice
void free_matrix(matrice_s * m)
{
	int i;
	if(m != NULL)
	{
		for(i = 0 ; i < m->nbl ; i++)
		{
			if(m->matrice[i] != NULL)
				free(m->matrice[i]);
		}
		if(m->matrice != NULL)
			free(m->matrice);
		free(m);
	}
}
// Suppression d'un polynôme
void free_polynome(polynome_s * p)
{
	if( p == NULL )
		return;

	free_matrix(p);
}
// Suppression d'une matrice de polynôme (pmatrice_s)
void free_pmatrice(pmatrice_s * pm)
{
	int i,j;
	if(pm == NULL)
		return ;
	for(i = 0 ; i < pm->nbl ; i++)
		for(j = 0 ; j < pm->nbc ; j++)
			if(pm->matrice[i][j] != NULL)
				free_polynome(pm->matrice[i][j]);
	for(i = 0 ; i < pm->nbl ; i++)
		free(pm->matrice[i]);

	free(pm->matrice);
	free(pm);
}
// Lire une matrice sur la ligne de comamnde
matrice_s * read_matrix( int nbl, int nbc ) 
{
	int i,j;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	matrice_s * m = malloc(sizeof(matrice_s));
	m->nbc = nbc;
	m->nbl = nbl;
	for(i=0; i < nbl ;i++)
		t[i] = malloc(nbc * sizeof(float));
	for(i=0;i<nbl;i++)
	{
		for(j=0;j<nbc;j++)
		{
			printf("Ligne %2d Colonne %2d : ",i,j);
			scanf("%f", &t[i][j]);
		}
	}
	m->matrice = t;
	return m;
}
// On crée et on rempli une matrice de manière aléatoire
matrice_s * random_matrix(int nbl, int nbc)
{
	matrice_s * m;
	m = create_matrix(nbl, nbc);
	remplir_alea(m);
	return m;
}
// On rempli une matrice de manière aléatoire
void remplir_alea(matrice_s * m)
{
	int i,j;
	static int remplir_alea_first = 0;

	if (remplir_alea_first == 0)
	{
		srand (time (NULL));
		remplir_alea_first = 1;
	}
	for( i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			m->matrice[i][j] = (rand() % 4) +1;
}
// Création d'un polynôme de premier
polynome_s * creation_poly_prem(float x1, float x)
{
	matrice_s * m = create_matrix(1,2);
	m->matrice[0][0] = x;
	m->matrice[0][1] = x1;

	return (polynome_s *) m;
}
// Création d'un polynôme de second degré
polynome_s * creation_poly_sec(float x2, float x1, float x)
{
	matrice_s * m = create_matrix(1,3);
	m->matrice[0][0] = x;
	m->matrice[0][1] = x1;
	m->matrice[0][2] = x2;

	return (polynome_s *) m;
}
// Créer une pmatrice_s qui est une matrice avec des polynômes sur la diagonale
pmatrice_s * create_matrix_poly(matrice_s * m)
{
	int i, j;
	float tmp;
	pmatrice_s * res = malloc(sizeof(pmatrice_s));
	res->nbl = m->nbl;
	res->nbc = m->nbc;
	
	res->matrice = (polynome_s ***) malloc(sizeof(polynome_s**) * m->nbl);
	for(i = 0 ; i < m->nbl ; i++)
		res->matrice[i] = (polynome_s **) malloc(sizeof(polynome_s*) * m->nbc);

	for(i = 0 ; i < m->nbl ; i++)
	{
		for(j = 0 ; j < m->nbc ; j++)
		{
			// Si on est sur la diagonale, on a -delta
			if(i == j)
				tmp = -1;
			else
				tmp = 0;

			res->matrice[i][j] = creation_poly_prem(tmp, m->matrice[i][j]);
		}
	}

	return res;
}
// affichage brut des données d'un polynôme
void display_polynome_core(polynome_s * p)
{
	if(p == NULL) return; // Protection contre les segfaults

	int i;
	for(i = p->nbc -1 ; i >= 0 ; i--)
	{
		if(p->matrice[0][i] >= 0)
			printf("+");
		if(i == 1)
			printf("%3.2lfx  ", p->matrice[0][i]);
		else if( i == 0 )
			printf("%3.2lf  ", p->matrice[0][i]);
		else
			printf("%3.2lfx^%d  ", p->matrice[0][i] , i);
	}
}

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
	polynome_s * resultat = dupliquer_polynome(p);
	for(i = 0 ; i < resultat->nbc ; i++)
		resultat->matrice[0][i] = resultat->matrice[0][i] * reel;

	return resultat;
}
// Duplication d'un polynôme
polynome_s * dupliquer_polynome(polynome_s * p)
{
	return (polynome_s *) dupliquer_matrice((matrice_s *) p);
}
matrice_s * get_matrice_generatrice(void)
{
	matrice_s * m;
	m = create_matrix(4, 8);

	// In
	m->matrice[0][0] = 1;
	m->matrice[1][1] = 1;
	m->matrice[2][2] = 1;
	m->matrice[3][3] = 1;

	// At
	m->matrice[1][4] = 1; m->matrice[2][4] = 1; m->matrice[3][4] = 1;
	m->matrice[0][5] = 1; m->matrice[2][5] = 1; m->matrice[3][5] = 1;
	m->matrice[0][6] = 1; m->matrice[1][6] = 1; m->matrice[3][6] = 1;
	m->matrice[0][7] = 1; m->matrice[1][7] = 1; m->matrice[2][7] = 1;

	return m;
}
matrice_s * get_matrice_parite(void)
{
	matrice_s * m = create_matrix(4, 8);

	// A
	m->matrice[1][0] = 1; m->matrice[2][0] = 1; m->matrice[3][0] = 1;
	m->matrice[0][1] = 1; m->matrice[2][1] = 1; m->matrice[3][1] = 1;
	m->matrice[0][2] = 1; m->matrice[1][2] = 1; m->matrice[3][2] = 1;
	m->matrice[0][3] = 1; m->matrice[1][3] = 1; m->matrice[2][3] = 1;

	// In
	m->matrice[0][4] = 1;
	m->matrice[1][5] = 1;
	m->matrice[2][6] = 1;
	m->matrice[3][7] = 1;

	return m;
}
void matrice_mod_2(matrice_s * m)
{
	int i, j;
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			while(m->matrice[i][j] >= 2)
				m->matrice[i][j] -= 2;
}
