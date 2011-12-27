#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

#include "base.h"

void display_matrix(matrice_s * m) 
{
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
			m->matrice[i][j] = (rand() % 3) +1;
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
