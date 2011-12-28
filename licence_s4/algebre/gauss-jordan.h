#ifndef __GAUSS_JORDAN_H__
#define __GAUSS_JORDAN_H__

int systeme_gauss_jordan(matrice_s * m1, matrice_s * inverse);

// Recherche la ligne du prochain pivot, en partant d'une ligne et d'une colonne
// Retourne la ligne pivot ou -1 s'il n'y a pas 
// Et la colonne pivot est renseignée
int recherche_ligne_pivot_suivant(matrice_s * m, int l_depart, int * c_depart);

#endif

