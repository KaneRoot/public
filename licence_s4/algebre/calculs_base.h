#ifndef CALCULS_BASE
#define CALCULS_BASE

matrice_s * add_matrix(matrice_s * m1, matrice_s * m2);
matrice_s * multiplication_matrices(matrice_s *m1, matrice_s *m2);
matrice_s * transposee_matrix(matrice_s *m);

// addition_lignes( matrice , ligne de départ , ligne à multiplier , coefficient multiplicateur)
matrice_s * addition_lignes(matrice_s * , int, int, float);

// Inversion de 2 lignes
matrice_s * inversion_lignes(matrice_s * m , int l1, int l2);

#endif
