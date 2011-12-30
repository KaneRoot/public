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

// Permet de savoir où on a une ligne avec 2 valeurs == 0
int pattern_detector_line(pmatrice_s * p)
{
	int res = -1;
	int i, j, n;

	for(i = 0 ; res == -1 && i < p->nbl ; i++)
	{
		n = 0;
		for(j = 0 ; j < p->nbc ; j++)
			if(0 == polynome_vide(p->matrice[i][j]))
				n++;
		if( n == 2)
			res = i;
	}

	return res;
}
// Permet de savoir où on a une colonne avec 2 valeurs == 0
int pattern_detector_column(pmatrice_s * p)
{
	int res = -1;
	int i, j, n;

	for(i = 0 ; res == -1 && i < p->nbc ; i++)
	{
		n = 0;
		for(j = 0 ; j < p->nbl ; j++)
			if(0 == polynome_vide(p->matrice[j][i]))
				n++;
		if( n == 2)
			res = i;
	}

	return res;
}

matrice_s * calcul_delta(polynome_s *p)
{
	matrice_s * m;
	float a = p->matrice[0][2];
	float b = p->matrice[0][1];
	float c = p->matrice[0][0];
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


