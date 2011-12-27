#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "comatrice.h"

#define T_MAT_MULT 3
#define T_MAT_DET 3
#define T_MAT_INVERSE 3


void test_determinant()
{
	matrice_s *m;

	printf("\033[31mTest de calcul du déterminant\033[00m \n");
	m = create_matrix(T_MAT_DET,T_MAT_DET);
	remplir_alea(m);
	printf("Création d'une matrice 4x4\n");
	printf("Display Matrix\n");
	display_matrix(m);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	free_matrix(m);
}
void test_comatrice()
{
	printf("\033[31mTest de la création d'une co-matrice\033[00m\n");
	matrice_s *m, *co;

	m = create_matrix(T_MAT_DET,T_MAT_DET);
	remplir_alea(m);
	printf("Création d'une matrice 4x4\n");
	display_matrix(m);
	printf("\nSa comatrice : \n");
	co = comatrice(m);
	display_matrix(co);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	free_matrix(co);
	free_matrix(m);
}
void test_inverse_gauss()
{
	matrice_s *m, *inverse;

	printf("\033[31mTest de calcul de l'inverse de la matrice - GAUSS\033[00m\n");
	printf("Création d'une matrice %dx%d\n",T_MAT_INVERSE,T_MAT_INVERSE);

//	m = create_matrix(T_MAT_INVERSE,T_MAT_INVERSE);
//	remplir_alea(m);
	m = read_matrix(T_MAT_INVERSE,T_MAT_INVERSE);

	display_matrix(m);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	inverse = inversion_gauss_jordan(m);

	printf("Inversion via Gauss-Jordan :\n");
	if(inverse != NULL)
		display_matrix(inverse);
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");
	
	free_matrix(inverse);
	free_matrix(m);
}
void test_inverse_comatrice()
{
	matrice_s *m, *co, *inverse;

	printf("\033[31mTest de calcul de l'inverse de la matrice - COMATRICE\033[00m\n");

	m = create_matrix(T_MAT_INVERSE,T_MAT_INVERSE);
	remplir_alea(m);
	printf("Création d'une matrice %dx%d\n",T_MAT_INVERSE,T_MAT_INVERSE);
	display_matrix(m);
	printf("\nCo-matrice : \n\n");
	co = comatrice(m);
	display_matrix(co);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	inverse = inversion_comatrices(m);
	printf("Inversion via co-matrice :\n");
	if(inverse != NULL)
		display_matrix(inverse);
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");
	free_matrix(inverse);
	printf("via gauss : \n");
	inverse = inversion_gauss_jordan(m);
	display_matrix(inverse);

	free_matrix(co);
	free_matrix(inverse);
	free_matrix(m);
}
void tests_calculs_base()
{
	matrice_s *m1, *m2,*m3,*multiplication, *transposee;

	printf("\033[31mCréation + remplissage de 2 matrices\033[00m\n");
	m1 = create_matrix(T_MAT_MULT,T_MAT_MULT);
	m2 = create_matrix(T_MAT_MULT,T_MAT_MULT);
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
void test_addition_lignes()
{
	printf("\033[31mAddition de 2 lignes\033[00m\n");
	matrice_s * m = create_matrix(T_MAT_MULT,T_MAT_MULT);
	remplir_alea(m);
	display_matrix(m);

	printf("Addition de 2 lignes : l1 += l0 * 2\n\n");
	addition_lignes(m,0, 1, 2);
	display_matrix(m);
	printf("Inversion de 2 lignes : la 2 et la 3\n\n");
	inversion_lignes(m, 2,3);
	display_matrix(m);
	
}
void tests_divers()
{
	printf("Matrice identitée de %d \n", T_MAT_MULT);
	matrice_s * identitee;
	identitee = matrice_identitee(T_MAT_MULT);
	display_matrix(identitee);

	matrice_s * autre = matrice_identitee(T_MAT_MULT);


	printf("Test fonction 'identiques' → si 2 matrices sont identiques\n");
	printf("Seconde matrice pour le test : \n");
	autre->matrice[0][0] = 2; 
	display_matrix(autre);

	if(identiques(autre,identitee) == 0)
		printf("Les 2 matrices sont identiques -- erreur\n");
	else
		printf("Les 2 matrices sont différentes -- fonction 'identiques' OK\n");

	int ligne, colonne;
	ligne = 1; colonne = 2;
	printf( "\n\033[31mTest du pivot\033[00m \n"
			"On prend la matrice identitée pour ce test\n"
			"On se place en ligne %d et en colonne %d" 
			": où est le prochain pivot ?\n",
			ligne, colonne);
	ligne = recherche_ligne_pivot_suivant(identitee, ligne, &colonne);
	printf("ligne trouvée : %d ::::: colonne : %d \n", ligne, colonne);
}
int main(int argc, char * argv[])
{
//	tests_calculs_base();
//	test_determinant();
//	test_comatrice();
//	test_addition_lignes();
	test_inverse_gauss(); // TODO
	//test_inverse_comatrice(); // TODO
	//tests_divers(); 
	return EXIT_SUCCESS;
}
