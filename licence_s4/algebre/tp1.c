#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;


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

float calcul_determinant_nxn(matrice_s *m)
{
	if(m == NULL || m->nbc != m->nbl)
		return -1.0;

	if(m->nbl == 2 && m->nbc == 2)
		return (m->matrice[0][0] * m->matrice[1][1]) - (m->matrice[1][0] * m->matrice[0][1]);

	float somme = 0;
	int i, j,k,l,tmpk = 0, tmpl = 0;
	matrice_s * tmp;
	for(i = 0 ; i < m->nbl ; i++)
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
matrice_s * transposee_matrix(matrice_s *m)
{
	int i,j;
	matrice_s * t = create_matrix(m->nbc, m->nbl);
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			t->matrice[j][i] = m->matrice[i][j];
	return t;
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
			m->matrice[i][j] = (rand() + 4) % 20;
}
void test_determinant()
{
	float f;
	matrice_s *m;

	printf("Test de calcul du déterminant \n");

	m = create_matrix(3,3);
	remplir_alea(m);
	printf("Création d'une matrice 4x4\n");
	printf("Display Matrix\n");
	display_matrix(m);
	f = calcul_determinant_nxn(m);
	printf("Déterminant de la matrice : %f\n",f);

	free_matrix(m);
}
void test_multiplication_addition()
{
	matrice_s *m1, *m2,*m3,*multiplication, *transposee;

	printf("Création + remplissage de 2 matrices\n");
	m1 = create_matrix(3,3);
	m2 = create_matrix(3,3);
	remplir_alea(m1);
	remplir_alea(m2);

	printf("Affichage des matrices\n");
	display_matrix(m1);
	display_matrix(m2);
	printf("Addition des matrices précédentes : \n");
	m3 = add_matrix(m1,m2);
	display_matrix(m3);

	printf("Multiplication de m1 et m2\n");
	multiplication = multiplication_matrices(m1,m2);
	display_matrix(multiplication);
	printf("Transposée de m1 \n");
	transposee = transposee_matrix(m1);
	display_matrix(transposee);

	free_matrix(m1);
	free_matrix(m2);
	free_matrix(m3);
	free_matrix(multiplication);
	free_matrix(transposee);
}
int main(int argc, char * argv[])
{
	//test_multiplication_addition();
	test_determinant();

	return EXIT_SUCCESS;
}
