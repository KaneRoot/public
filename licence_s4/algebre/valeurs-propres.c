#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "pivot-gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


matrice_s * valeurs_propres(matrice_s * m)
{
	matrice_s * vpropres;
	vpropres = create_matrix(m->nbl,1);

	return vpropres;
}

polynome_s * creation_poly_sec(float x2, float x1, float x)
{
	matrice_s * m = create_matrix(1,3);
	m->matrice[0][2] = x;
	m->matrice[0][1] = x1;
	m->matrice[0][0] = x2;

	return (polynome_s *) m;
}


