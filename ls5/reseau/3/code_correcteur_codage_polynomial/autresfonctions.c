#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codingdecoding.h"
#include "autresfonctions.h"
#include "logic.h"


// Récupérer l'adresse du premier bit à 1
int getFirstBitToOne(CodeWord_t * cw)
{
	int i;
	for(i = 16 ; i >= 0 ; i--)
		if(getNthBit(cw[0], i))
			return i;
	return 0;
}
void deplacementBits(CodeWord_t * cw, int nb)
{
	cw[0] = cw[0] << nb;
}
CodeWord_t getNombreDiviseur(void)
{
	CodeWord_t nbdiviseur;
	setNthBitCW(&nbdiviseur, 1, 1);
	setNthBitCW(&nbdiviseur, 4, 1);
	setNthBitCW(&nbdiviseur, 5, 1);
	setNthBitCW(&nbdiviseur, 6, 1);
	setNthBitCW(&nbdiviseur, 9, 1);
	return nbdiviseur;
}
void division(CodeWord_t *x)
{
	CodeWord_t ntmp = *x;
	CodeWord_t nombre_diviseur = getNombreDiviseur();

	printf("Division \n");

	while( getFirstBitToOne(&ntmp) > 8 && ntmp != 0)
	{
		deplacementBits(&nombre_diviseur, getFirstBitToOne(&ntmp) - getFirstBitToOne(&nombre_diviseur));
		ntmp = ntmp ^ nombre_diviseur;
//		printBits(nombre_diviseur, "nb : ");
		nombre_diviseur = getNombreDiviseur();
//		printBits(nombre_diviseur, "nb : ");
//		printBits(ntmp, "APRES : ");
	}
	*x += ntmp;
	printf(" --- Division \n");
}
void coder(CodeWord_t *cw)
{
	printBits(cw[0], "AVANT : ");
	deplacementBits(cw, 8);
	division(cw);
	printBits(cw[0], "APRES : ");
}
