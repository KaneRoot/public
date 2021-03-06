#ifndef __VALEURS_PROPRES_H__
#define __VALEURS_PROPRES_H__

// Calcule les valeurs propres et les renvoie dans une matrice 3x1
matrice_s * valeurs_propres(pmatrice_s * pm);
// Permet de savoir où on a une ligne avec 2 valeurs == 0
// retourne le numéro de ligne ou -1 s'il n'y a pas
int pattern_detector_line(pmatrice_s * p);

// Permet de savoir où on a une colonne avec 2 valeurs == 0
// retourne le numéro de colonne ou -1 s'il n'y a pas
int pattern_detector_column(pmatrice_s * p);

// On résoud une équation du second degré
matrice_s * resolution_equation_second_degre(polynome_s *p);

#endif

