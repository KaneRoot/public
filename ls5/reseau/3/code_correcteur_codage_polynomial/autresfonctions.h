#ifndef __AUTRES_FONCTIONS_H__
#define __AUTRES_FONCTIONS_H__

#define NB_DIVISEUR 285

// Récupérer l'adresse du premier bit à 1
int getFirstBitToOne(CodeWord_t * cw);
void deplacementBits(CodeWord_t * cw, int nb);
CodeWord_t getNombreDiviseur(void);
CodeWord_t division(CodeWord_t *x);

int decoder(CodeWord_t *cw);

#endif

