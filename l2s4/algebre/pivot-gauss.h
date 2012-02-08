#ifndef __PIVOT_GAUSS_H__
#define __PIVOT_GAUSS_H__


// Applique le pivot de Gauss à la première matrice 
// et fait les additions/inversions de lignes sur les 2 matrices
// Résultat : m2 = l'inverse si en entrée c'est la matrice identité
int pivot_gauss_double_matrice(matrice_s * m1, matrice_s * m2);

// Recherche la ligne du prochain pivot, en partant d'une ligne et d'une colonne
// Retourne la ligne pivot ou -1 s'il n'y a pas 
// Et la colonne pivot est renseignée
int recherche_ligne_pivot_suivant(matrice_s * m, int l_depart, int * c_depart);

#endif

