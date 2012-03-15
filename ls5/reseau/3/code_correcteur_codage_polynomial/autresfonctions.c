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
void division(CodeWord_t *x)
{
	int decalage;
	CodeWord_t ntmp = x[0];
	CodeWord_t nombre_diviseur = NB_DIVISEUR;

	printf("Division \n");

	printf("X : %u\n", ntmp);
	while( *x >= (CodeWord_t) 256 && *x != 0)
	{
		decalage = getFirstBitToOne(&ntmp) - getFirstBitToOne(&nombre_diviseur);
		deplacementBits(&ntmp, decalage);
		printBits(ntmp, "Nombre diviseur :");
		*x = *x ^ ntmp;
	}
	printf(" --- Division \n");
}
void coder(CodeWord_t *cw)
{
	deplacementBits(&cw[0], 16 - getFirstBitToOne(&cw[0]));
	division(cw);
	printBits(cw[0], "APRES : ");
}
