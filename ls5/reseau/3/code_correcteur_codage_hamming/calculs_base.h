#ifndef __CALCULS_BASE_H__
#define __CALCULS_BASE_H__

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
#endif
