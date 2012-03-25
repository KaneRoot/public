#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codingdecoding.h"
#include "autresfonctions.h"
#include "logic.h"


// Récupérer le degré d'un polynôme
int getDegre(CodeWord_t * cw)
{
	int i;
	for(i = 15 ; i >= 0 ; i--)
		if(getNthBit(cw[0], i))
			return i;
	return 0;
}
// Déplacement de bits
void deplacementBits(CodeWord_t * cw, int nb)
{
	*cw = (nb > 0) ? *cw << nb : *cw >> -nb;
}
// Renvoie le polynôme diviseur sous forme de CodeWord_t
CodeWord_t getNombreDiviseur(void)
{
	CodeWord_t nbdiviseur;
	setNthBitCW(&nbdiviseur, 1, 1);
	setNthBitCW(&nbdiviseur, 3, 1);
	setNthBitCW(&nbdiviseur, 4, 1);
	setNthBitCW(&nbdiviseur, 5, 1);
	setNthBitCW(&nbdiviseur, 9, 1);
	return nbdiviseur;
}
// Effectuer la division d'un polynôme
CodeWord_t division(CodeWord_t *x)
{
	CodeWord_t ntmp = *x;
	CodeWord_t nombre_diviseur = getNombreDiviseur();
	int deplacement;

	// tant que le degré du polynôme diviseur est inférieur ou égal à l'autre
	while( (deplacement = getDegre(&ntmp) - getDegre(&nombre_diviseur)) >= 0)
	{
		// nombre_diviseur est une variable temporaire contenant le polynôme diviseur
		deplacementBits(&nombre_diviseur, deplacement);
		ntmp = ntmp ^ nombre_diviseur;
		nombre_diviseur = getNombreDiviseur();
	}
	return ntmp;
}
