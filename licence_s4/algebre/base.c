#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

#include "base.h"

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
matrice_s * random_matrix(int nbl, int nbc)
{
	matrice_s * m;
	m = create_matrix(nbl, nbc);
	remplir_alea(m);
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
			m->matrice[i][j] = (rand() % 4) +1;
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
polynome_s * creation_poly_prem(float x1, float x)
{
	matrice_s * m = create_matrix(1,2);
	m->matrice[0][0] = x;
	m->matrice[0][1] = x1;

	return (polynome_s *) m;
}
polynome_s * creation_poly_sec(float x2, float x1, float x)
{
	matrice_s * m = create_matrix(1,3);
	m->matrice[0][0] = x;
	m->matrice[0][1] = x1;
	m->matrice[0][2] = x2;

	return (polynome_s *) m;
}
void free_polynome(polynome_s * p)
{
	if( p == NULL )
		return;

	free_matrix(p);
}
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

void display_polynome(polynome_s * p)
{
	int i;
	if(p == NULL)
	{
		printf("\033[31mPas de polynôme ! \033[00m\n");
		return ;
	}

	printf("\033[32mPolynôme : [[ \033[00m ");

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
//	if(p->matrice[0][1] != 0)
//		printf("%3.2lfx  ",p->matrice[0][1]);
//	if(p->matrice[0][0] != 0)
//		printf("%3.2lf ",p->matrice[0][0]);
	printf("\033[32m ]] \033[00m \n");
}

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
