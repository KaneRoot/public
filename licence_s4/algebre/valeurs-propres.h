#ifndef __VALEURS_PROPRES_H__
#define __VALEURS_PROPRES_H__

// Permet de savoir où on a une ligne avec 2 valeurs == 0
// retourne le numéro de ligne ou -1 s'il n'y a pas
int pattern_detector_line(pmatrice_s * p);

// Permet de savoir où on a une colonne avec 2 valeurs == 0
// retourne le numéro de colonne ou -1 s'il n'y a pas
int pattern_detector_column(pmatrice_s * p);

#endif

