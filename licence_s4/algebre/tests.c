#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "comatrice.h"
#include "gauss-jordan.h"

#define T_MAT_MULT 3
#define T_MAT_DET 3
#define T_MAT_INVERSE 3

void choix_nbl_nbc(int * nbl, int * nbc)
{
	printf("Nombre de lignes : ");
	scanf("%d",nbl);
	printf("Nombre de colonnes : ");
	scanf("%d",nbc);
}
matrice_s * creation_matrice()
{
	matrice_s * m;
	int nbl, nbc;
	int choix = 0;
	printf("Création d'une matrice, \033[31m-- choix de la dimension\033[00m\n");
	choix_nbl_nbc(&nbl, &nbc);
	printf(	"Choix 1 : remplissage aléatoire de la matrice\n"
			"Choix 2 : remplir soi-même\n");
	scanf("%d",&choix);
	switch(choix)
	{
		case 1 : m = random_matrix(nbl, nbc); break;
		case 2 : m = read_matrix(nbl, nbc); break;
		default : break;
	}
	return m;
}

void test_determinant()
{
	matrice_s *m;

	printf("Test : calcul du déterminant \033[31m-- création d'une matrice\033[00m\n");
	m = creation_matrice();

	printf("Display Matrix\n");
	display_matrix(m);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	free_matrix(m);
}
void test_comatrice()
{
	printf("\033[31mTest de la création d'une co-matrice\033[00m\n");
	matrice_s *m, *co;

	m = random_matrix(T_MAT_DET,T_MAT_DET);
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
	m = creation_matrice();
	display_matrix(m);

	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	printf("Inversion via Gauss-Jordan :\n");
	inverse = inversion_gauss_jordan(m);
	if(inverse != NULL)
		display_matrix(inverse);
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");
	
	//inversion_lignes(inverse, 0,1);
	matrice_s * multiplication = multiplication_matrices(m,inverse);

	printf("multiplication inverse et m\n");
	display_matrix(multiplication);
	free_matrix(inverse);
	free_matrix(m);
}
void test_inverse_comatrice()
{
	matrice_s *m, *co, *inverse;

	printf("\033[31mTest de calcul de l'inverse de la matrice - COMATRICE\033[00m\n");

	m = read_matrix(T_MAT_INVERSE,T_MAT_INVERSE);
	printf("Création d'une matrice %dx%d\n",T_MAT_INVERSE,T_MAT_INVERSE);
	display_matrix(m);
	printf("\nCo-matrice : \n\n");
	co = comatrice(m);
	display_matrix(co);
	printf("Déterminant de la matrice : %f\n",det_nxn(m));

	inverse = inversion_comatrices(m);
	printf("Inversion via co-matrice :\n");
	if(inverse != NULL)
	{
		display_matrix(inverse);
		matrice_s * multiplication = multiplication_matrices(m,inverse);

		printf("multiplication inverse et m\n");
		display_matrix(multiplication);
	}
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");

//	free_matrix(inverse);
//	printf("via gauss : \n");
//	inverse = inversion_gauss_jordan(m);
//	display_matrix(inverse);

	free_matrix(co);
	free_matrix(inverse);
	free_matrix(m);
}
void tests_calculs_base()
{
	matrice_s *m1, *m2,*m3,*multiplication, *transposee;

	printf("\033[31mCréation + remplissage de 2 matrices\033[00m\n");
	m1 = random_matrix(T_MAT_MULT,T_MAT_MULT);
	m2 = random_matrix(T_MAT_MULT,T_MAT_MULT);

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
void test_multiplication()
{
	printf("\033[31mtest de la multiplication : création de 2 matrices\033[00m\n");
	matrice_s *m1, *m2, *mult;
	m1 = creation_matrice();
	m2 = creation_matrice();

	printf("Les 2 matrices crées : \n");
	display_matrix(m1);
	display_matrix(m2);

	printf("Multiplication de ces 2 matrices : \n");
	mult = multiplication_matrices(m1,m2);
	display_matrix(mult);

}
void test_addition_matrices()
{
	printf("test addition de matrices \033[31m -- création de 2 matrices \033[00m\n");
	matrice_s * m1, *m2;
	m1 = creation_matrice();
	m2 = creation_matrice();

	printf("Affichage des matrices créées : \n");
	display_matrix(m1);
	display_matrix(m2);

	
}
// TODO
void test_inversion()
{
	test_inverse_comatrice();
	test_inverse_gauss();
}
void test_addition_lignes()
{
	printf("\033[31mAddition de 2 lignes\033[00m\n");
	matrice_s * m = random_matrix(T_MAT_MULT,T_MAT_MULT);
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
void test_systeme_gauss()
{
	matrice_s *m, *valeur;

	printf("\033[31mTest de calcul de l'valeur de la matrice - GAUSS\033[00m\n");
	printf("Création d'une matrice %dx%d\n",T_MAT_INVERSE,T_MAT_INVERSE);

	m = read_matrix(T_MAT_INVERSE,T_MAT_INVERSE);

	display_matrix(m);
	printf("Création d'une matrice %dx1\n",T_MAT_INVERSE);
	valeur = read_matrix(T_MAT_INVERSE,1);

	printf("Résolution du système via le pivot de Gauss :\n");

	if(systeme_gauss_jordan(m,valeur) == 0)
		display_matrix(valeur);
	else
		printf("impossible de résoudre ce système !\n");
	
	free_matrix(valeur);
	free_matrix(m);
}
void print_menu()
{
	printf(	"\n\n	\033[31mMENU\033[00m\n"
			" 1 : déterminant d'une matrice\n"
			" 2 : addition de 2 matrices\n"
			" 3 : multiplications de 2 matrices\n"
			" 4 : comatrice\n"
			" 5 : inversion - via comatrice puis par pivot\n"
			"Votre choix : "
		  );
}
void menu()
{
	int choix;
	while(1)
	{
		choix = -1;
		print_menu();

		scanf("%d",&choix);
		switch(choix)
		{
			case 1 : test_determinant();
			case 2 : test_addition_matrices(); break;
			case 3 : test_multiplication(); break; // TODO
			case 4 : test_comatrice(); break;
			case 5 : test_inversion(); break; // TODO
			default : 
				printf("\033[32mERREUR CHOIX\033[00m\n");
				break;

		}
	}

//	tests_calculs_base();
//	test_multiplication();
//	test_determinant();
//	test_comatrice();
//	test_addition_lignes();
//	test_inverse_comatrice();
//	test_inverse_gauss(); // TODO
//	tests_divers(); 
//	test_systeme_gauss();

}
int main(int argc, char * argv[])
{
	menu();
	return EXIT_SUCCESS;
}
