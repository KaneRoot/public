#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codingdecoding.h"
#include "autresfonctions.h"
#include "logic.h"


// Récupérer l'adresse du premier bit à 1
int getDegre(CodeWord_t * cw)
{
	int i;
	for(i = 15 ; i >= 0 ; i--)
		if(getNthBit(cw[0], i))
			return i;
	return 0;
}
void deplacementBits(CodeWord_t * cw, int nb)
{
	*cw = (nb > 0) ? *cw << nb : *cw >> -nb;
}
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
CodeWord_t division(CodeWord_t *x)
{
	CodeWord_t ntmp = *x;
	CodeWord_t nombre_diviseur = getNombreDiviseur();
	printf("%d nombre diviseur\n", nombre_diviseur);
	int deplacement;

	while( (deplacement = getDegre(&ntmp) - getDegre(&nombre_diviseur)) >= 0)
	{
		printf("PREMIER BIT : %d\n", getDegre(&ntmp));
		printf("Déplacement : %d\n", getDegre(&ntmp) - getDegre(&nombre_diviseur));
		deplacementBits(&nombre_diviseur, deplacement);
		printBits(nombre_diviseur, "nombre diviseur");
		ntmp = ntmp ^ nombre_diviseur;
		nombre_diviseur = getNombreDiviseur();
	}
	printBits(ntmp, "Reste de la division : ");
	return ntmp;
}
