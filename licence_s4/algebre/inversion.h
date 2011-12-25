#ifndef INVERSION
#define INVERSION

matrice_s * inversion_gauss_jordan(matrice_s * m);
matrice_s * inversion_comatrices(matrice_s * m);

// Recherche la ligne du prochain pivot, en partant d'une ligne et d'une colonne
// Retourne la ligne pivot ou -1 s'il n'y a pas 
// Et la colonne pivot est renseignée
int recherche_ligne_pivot_suivant(matrice_s * m, int l_depart, int * c_depart);

#endif
