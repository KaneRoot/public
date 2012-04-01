#ifndef __MESFONCTIONS_H__
#define __MESFONCTIONS_H__

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

matrice_s * add_matrix(matrice_s * m1, matrice_s * m2);
matrice_s * multiplication_matrices(matrice_s *m1, matrice_s *m2);
matrice_s * transposee_matrix(matrice_s *m);

// addition_lignes( matrice , ligne de départ , ligne à multiplier , coefficient multiplicateur)
matrice_s * addition_lignes(matrice_s * , int, int, float);

// Inversion de 2 lignes
matrice_s * inversion_lignes(matrice_s * m , int l1, int l2);

// Calcul matrice identitée
matrice_s * matrice_identitee(int taille);

// Faire une copie d'une matrice
matrice_s * dupliquer_matrice(matrice_s * m);

// Inversion de 2 lignes dans une pmatrice (matrice de polynômes)
void pmatrice_inversion_lignes(pmatrice_s * pm, int ligne1, int ligne2);

// Inversion de 2 colonnes dans une pmatrice (matrice de polynômes)
void pmatrice_inversion_colonnes(pmatrice_s * pm, int col1, int col2); 

// Multiplication de polynômes	!!!		de premier degré	!!!
polynome_s * multiplication_polynomes_prem(polynome_s * p1, polynome_s * p2);

// Soustraction de polynômes de second degré
polynome_s * soustraction_polynomes_sec(polynome_s * p1, polynome_s * p2);

// On cherche à savoir si le polynôme est vide
// 0 si vide, 1 sinon
int polynome_vide(polynome_s * p);

// Savoir si 2 matrices sont les mêmes
int identiques(matrice_s *, matrice_s *);

// ligne de départ = ligne de départ + coeff * une autre
void pmatrice_addition_lignes(pmatrice_s * pm, int l_depart, int l_a_mul, float coeff);
polynome_s * addition_polynomes_prem(polynome_s * p1, polynome_s * p2);

// Multiplication d'un polynôme par un réel
polynome_s * multiplication_polynome_par_reel(polynome_s * p, float reel);

// Duplication d'un polynôme
polynome_s * dupliquer_polynome(polynome_s * p);

matrice_s * get_matrice_generatrice(void);
matrice_s * get_matrice_parite(void);
void matrice_mod_2(matrice_s * m);
#endif
