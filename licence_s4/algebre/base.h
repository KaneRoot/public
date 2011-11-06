#ifndef BASE
#define BASE

typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;

// Affichage des matrices
void display_matrix(matrice_s * m);

// Alloue la place pour la matrice
matrice_s * create_matrix(int nbl, int nbc);

// Demande à l'utilisateur de rentrer la matrice
matrice_s * read_matrix( int nbl, int nbc );

// Remplir une matrice de manière aléatoire
void remplir_alea(matrice_s * m);

// Suppression propre des matrices
void free_matrix(matrice_s * m);

#endif
