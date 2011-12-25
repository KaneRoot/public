#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "comatrice.h"

#define TAILLE_MATRICE_MULTIPLICATION 4
#define TAILLE_MATRICE_DETERMINANT 3


void test_determinant()
{
	matrice_s *m, *co,*inverse;

	printf("Test de calcul du déterminant \n");

	m = create_matrix(TAILLE_MATRICE_DETERMINANT,TAILLE_MATRICE_DETERMINANT);
	remplir_alea(m);
	printf("Création d'une matrice 4x4\n");
	printf("Display Matrix\n");
	display_matrix(m);
	co = comatrice(m);
	display_matrix(co);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	inverse = inversion_comatrices(m);
	if(inverse != NULL)
		display_matrix(inverse);
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");

	
	free_matrix(co);
	free_matrix(inverse);
	free_matrix(m);
}
void tests_calculs_base()
{
	matrice_s *m1, *m2,*m3,*multiplication, *transposee;

	printf("Création + remplissage de 2 matrices\n");
	m1 = create_matrix(TAILLE_MATRICE_MULTIPLICATION,TAILLE_MATRICE_MULTIPLICATION);
	m2 = create_matrix(TAILLE_MATRICE_MULTIPLICATION,TAILLE_MATRICE_MULTIPLICATION);
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
	matrice_s * m = create_matrix(TAILLE_MATRICE_MULTIPLICATION,TAILLE_MATRICE_MULTIPLICATION);
	remplir_alea(m);
	display_matrix(m);

	addition_lignes(m,0, 1, 2);
	display_matrix(m);
	inversion_lignes(m, 2,3);
	display_matrix(m);

}
int main(int argc, char * argv[])
{
	//tests_calculs_base();
//	test_determinant();
	test_addition_lignes();


	return EXIT_SUCCESS;
}
