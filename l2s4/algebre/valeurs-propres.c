#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "pivot-gauss.h"
#include "valeurs-propres.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// On l'aura compris : calcul des valeurs propres
// Renvoie une matrice de pm->nbl valeurs
matrice_s * valeurs_propres(pmatrice_s * pm)
{
	int i, j, k, l, n = 0;
	polynome_s * polynomes_a_multiplier[4];
	polynome_s * polynomes_a_soustraire[2]; 
	float tmp;
	matrice_s * vpropres;
	polynome_s * ptmp = NULL;
	vpropres = create_matrix(pm->nbl,1);

	if( (i = pattern_detector_line(pm)) != -1)
	{
		for(j = 0 ; ptmp == NULL && j < pm->nbc ; j++)
		{
			if(polynome_vide(pm->matrice[i][j]) != 0)
				ptmp = pm->matrice[i][j];
		}
		j--; // À la fin de la boucle on va ajouter 1 à j alors qu'on ne le souhaite pas
		tmp = (ptmp->matrice[0][1] == 0.0) ? 1 : ptmp->matrice[0][1];
		vpropres->matrice[0][0] = (-1) * (ptmp->matrice[0][0]/tmp);
	}
	else if((j = pattern_detector_column(pm)) != -1)
	{
		for(i = 0 ; ptmp == NULL && i < pm->nbl ; i++)
		{
			if(polynome_vide(pm->matrice[i][j]) != 0)
				ptmp = pm->matrice[i][j];
		}
		i--; // À la fin de la boucle on va ajouter 1 à i alors qu'on ne le souhaite pas
		tmp = (ptmp->matrice[0][1] == 0.0) ? 1 : ptmp->matrice[0][1];
		// n = ( ((i%2 + j%2)%2) == 0 ) ? -1 : 1;  // Serait-ce inutile ? On dirait bien.
		vpropres->matrice[0][0] = (-1) * (ptmp->matrice[0][0]/tmp);
	}
	else
	{
		free_matrix(vpropres);
		return NULL;
	}
	n = 0;
	for(k = 0 ; k < pm->nbl ; k++)
		for(l = 0 ; l < pm->nbc ; l++)
			if(k != i && l != j)
				polynomes_a_multiplier[n++] = pm->matrice[k][l];


	polynomes_a_soustraire[0] = multiplication_polynomes_prem(polynomes_a_multiplier[0], polynomes_a_multiplier[3]);
	polynomes_a_soustraire[1] = multiplication_polynomes_prem(polynomes_a_multiplier[1], polynomes_a_multiplier[2]);

	ptmp = soustraction_polynomes_sec(polynomes_a_soustraire[0],polynomes_a_soustraire[1]);

	matrice_s * resolution = resolution_equation_second_degre(ptmp);

	// On recopie les valeurs trouvées dans vpropres
	// resolution ne peut avoir que 2 valeurs dans sa matrice au maximum
	for(i = 0 ; i < resolution->nbc ; i++)
		vpropres->matrice[i+1][0] = resolution->matrice[0][i];

	// Suppression propre des éléments devenus inutiles
	free_polynome(ptmp);
	free_matrix(resolution);
	free_polynome(polynomes_a_soustraire[0]);
	free_polynome(polynomes_a_soustraire[1]);

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

// On résoud une équation du second degré
matrice_s * resolution_equation_second_degre(polynome_s *p)
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
		m->matrice[0][0] = (-b - sqrt(d))/(2*a);
		m->matrice[0][1] = (-b + sqrt(d))/(2*a);
	}
	else if(d == 0)
	{
		m = create_matrix(1,1);
		m->matrice[0][0] = (-b)/(2*a);
	}

	return m;
}
