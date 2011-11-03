#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;


void display_matrix(matrice_s * m) 
{
	int i, j;

	printf( "     " );
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
	int i;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	for(i = 0 ; i < nbl ; i++)
		t[i] = (float*)malloc(nbc * sizeof(float));

	matrice_s * m = malloc(sizeof(matrice_s));
	m->matrice = t;
	m->nbl = nbl;
	m->nbc = nbc;
	return m;
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
matrice_s * add_matrix(matrice_s * m1, matrice_s * m2)
{
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
		return NULL;
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
int main(int argc, char * argv[])
{
	matrice_s *m1, *m2,*m3,*multiplication;

	printf("Création des matrices\n");
	m1 = read_matrix(2,2);
	m2 = read_matrix(2,2);
	printf("Affichage des matrices\n");
	display_matrix(m1);
	display_matrix(m2);
	printf("Addition des matrices précédentes : \n");
	m3 = add_matrix(m1,m2);
	// Affichage 
	display_matrix(m3);

	printf("Multiplication de m1 et m2\n");
	multiplication = multiplication_matrices(m1,m2);
	display_matrix(multiplication);


	//test_somme();
	//test_transposee();
	//test_multiplication();
	return EXIT_SUCCESS;
}
