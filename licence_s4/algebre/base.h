#ifndef __BASE_H__
#define __BASE_H__

typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;

typedef matrice_s polynome_s ;
typedef struct
{
	int nbl;
	int nbc;
	polynome_s ***matrice;
} pmatrice_s;

// Affichage des matrices
void display_matrix(matrice_s * m);

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

// Savoir si 2 matrices sont les mêmes
int identiques(matrice_s *, matrice_s *);

#endif
