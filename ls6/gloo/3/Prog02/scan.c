#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXNUM 12

/* Pour compiler, rajoutez l'argument "-lm" a l'appel de gcc  */

int main()
{
  char index;
  char * tableau;
  double taille = exp(MAXNUM);  
  tableau = malloc (4*taille*sizeof(char));
  for(index = 0; index<taille; index++)
      tableau[2*index] = index;

  return 0;
}
