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


matrice_s * calcul_delta(polynome_s *p)
{
	matrice_s * m;
	float a = p->matrice[2];
	float b = p->matrice[1];
	float c = p->matrice[0];
	float d = b*b - 4 * a * c;

	if( d < 0)
		d = -d;

	if( d > 0)
	{
		m = create_matrix(1,2);
		m->matrice[0][0] = (-b - racine(d))/(2*a);
		m->matrice[0][1] = (-b + racine(d))/(2*a);
	}
	else if(d == 0)
	{
		m = create_matrix(1,1);
		m->matrice[0][0] = (-b)/(2*a);
	}

	return m;
}
polynome_s * multiplication_polynomes_prem(polynome_s * p1, polynome_s * p2)
{
	polynome_s * resultat;

	resultat = creation_poly_sec(
			p1->matrice[0][1] * p2->matrice[0][1],
			p1->matrice[0][0] * p2->matrice[0][1] + p1->matrice[0][1] * p2->matrice[0][0],
			p1->matrice[0][0] * p2->matrice[0][0]);

	return resultat;
}

