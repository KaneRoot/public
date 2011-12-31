#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

#include "base.h"

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
