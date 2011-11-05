#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void affich_mat( float** mat, int nbl, int nbc ) 
{
	int i, j;

	printf( "     " );
	for ( i = 0 ; i < nbc ; i++ ) 
		printf( " %4d", i ); 
	printf( "\n     " );
	for ( i = 0 ; i < nbc ; i++ ) 
		printf( "-----" ); 
	printf( "\n" );

	for ( i = 0 ; i < nbl ; i++ ) 
	{
		printf( " %2d |", i );	
		for ( j = 0 ; j < nbc ; j++ )
			printf( " %2.2f", mat[i][j] );
		printf( "\n" );
	}
	printf( "\n" );
}
float** creer_matrice(int nbl, int nbc)
{
	int i;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	for(i = 0 ; i < nbl ; i++)
		t[i] = (float*)malloc(nbc * sizeof(float));
	return t;
}
float** lire_mat( int nbl, int nbc ) 
{

	int i,j;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	for(i=0;i<nbl;i++)
		t[i] = malloc(nbc * sizeof(float));
	for(i = 0 ; i < nbl ; i++ )
	{
		for(j = 0 ; j < nbc ; j++)
		{
			printf("Ligne %2d Colonne %2d : ",i,j);
			scanf("%f", &t[i][j]);
		}
	}
	return t;
}
// Les 2 matrices + nb de lignes + nb de colonnes
float** somme_matrices(float **m1, float **m2, int l, int c)
{
	int i, j;
	float **somme = creer_matrice(l,c);
	for(i = 0 ; i < l ; i++)
		for(j = 0 ; j < c ; j++)
			somme[i][j] = m1[i][j] + m2[i][j];
	return somme;
}
float ** multiplication_matrices(float **m1, float **m2, int nbl1, int nbc1, int nbl2, int nbc2)
{
	int i, j,k;
	int somme;
	if(nbc1 != nbl2)
		return NULL;
	float **m = creer_matrice(nbl1,nbc2);

	for(i = 0 ; i < nbl1; i++)
	{
		for(j = 0 ; j < nbc2 ; j++)
		{
			somme = 0;
			for(k = 0; k < nbc1 ; k++)
				somme += (m1[i][k] * m2[k][j]);
			m[i][j] = somme;
		}
	}
	return m;
}
void test_multiplication()
{
	int nbc1 = 2, nbc2 = 3;
	int nbl1 = 1, nbl2 = 2;
	float ** m1 = lire_mat(nbl1,nbc1);
	float ** m2 = lire_mat(nbl2,nbc2);

	float ** m = multiplication_matrices(m1,m2,nbl1,nbc1,nbl2,nbc2);
	affich_mat(m1,nbl1,nbc1);
	affich_mat(m2,nbl2,nbc2);

	affich_mat(m,nbl1,nbc2);

}
void test_somme()
{
	int nb_l = 2;
	int nb_c = 2;
	float ** m1;
	float ** m2;
	float ** somme;

	m1 = lire_mat(nb_l,nb_c);
	affich_mat(m1,nb_l,nb_c);
	m2 = lire_mat(nb_l,nb_c);
	affich_mat(m2,nb_l,nb_c);
	somme = somme_matrices(m1,m2,nb_l,nb_c);
	affich_mat(somme, nb_l,nb_c);
}
float ** transposee_matrice(float **m, int l, int c)
{
	int i,j;
	float ** t = creer_matrice(c,l);
	for(i = 0 ; i < l ; i++)
		for(j = 0 ; j < c ; j++)
			t[j][i] = m[i][j];
	return t;
}
void test_transposee()
{
	int nb_l = 2;
	int nb_c = 3;
	float ** m;
	float ** t;
	
	m = lire_mat(nb_l,nb_c);
	affich_mat(m,nb_l,nb_c);
	t = transposee_matrice(m,nb_l,nb_c);
	affich_mat(t,nb_c,nb_l);
}
int main(int argc, char * argv[])
{
	return EXIT_SUCCESS;
}
