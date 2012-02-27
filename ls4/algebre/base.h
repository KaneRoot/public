#ifndef __BASE_H__
#define __BASE_H__

// matrice_s : la matrice de base qui contient des floats
// On travaillera dessus la plupart du temps
typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;

typedef matrice_s polynome_s ;

// pmatrice_s = matrice comme plus haut mais avec des polynômes
// sert uniquement pour le calcul de valeurs propres
typedef struct
{
	int nbl;
	int nbc;
	polynome_s ***matrice;
} pmatrice_s;

// Affichage d'une pmatrice
void display_pmatrix(pmatrice_s * pm);

// Affichage des matrices
void display_matrix(matrice_s * m);

// Affichage d'un polynôme
void display_polynome(polynome_s * p);

// Alloue la place pour la matrice
matrice_s * create_matrix(int nbl, int nbc);

// Demande à l'utilisateur de rentrer la matrice
matrice_s * read_matrix( int nbl, int nbc );

// Créer une matrice aléatoire avec nbl lignes et nbc colonnes
matrice_s * random_matrix(int nbl, int nbc);

// Remplir une matrice de manière aléatoire
void remplir_alea(matrice_s * m);

// Suppression propre des matrices
void free_matrix(matrice_s * m);

// Suppression propre d'un polynôme
void free_polynome(polynome_s * p);
//
// Suppression d'une matrice de polynôme (pmatrice_s)
void free_pmatrice(pmatrice_s * pm);

// Création d'un polynôme de premier degré
polynome_s * creation_poly_prem(float x1, float x);

// Création d'un polynôme de second degré
polynome_s * creation_poly_sec(float x2, float x1, float x);

// affichage brut des données d'un polynôme
void display_polynome_core(polynome_s * p);

// Créer une pmatrice_s qui est une matrice avec des polynômes sur la diagonale
pmatrice_s * create_matrix_poly(matrice_s * m);

// Créer une pmatrice_s qui est une matrice avec des polynômes sur la diagonale
pmatrice_s * create_matrix_poly(matrice_s * m);

#endif
