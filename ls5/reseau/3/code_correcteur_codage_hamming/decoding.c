/**
 * @file decoding.c
 * @author Arash Habibi
 * @author Julien Montavont
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Functions to decipher the code words
 */

#include <stdio.h>
#include "codingdecoding.h"

void
copyDataBitsDecoding (CodeWord_t * cw, char *message, int data_size)
{
  int i = 0;

  for (i = 0; i < data_size; i++)
  {
    setNthBitW (&(message[i]), 1, getNthBit (cw[i], 1));
    setNthBitW (&(message[i]), 2, getNthBit (cw[i], 2));
    setNthBitW (&(message[i]), 3, getNthBit (cw[i], 3));
    setNthBitW (&(message[i]), 4, getNthBit (cw[i], 4));
    setNthBitW (&(message[i]), 5, getNthBit (cw[i], 5));
    setNthBitW (&(message[i]), 6, getNthBit (cw[i], 6));
    setNthBitW (&(message[i]), 7, getNthBit (cw[i], 7));
    setNthBitW (&(message[i]), 8, getNthBit (cw[i], 8));
  }
}

/*
void errorCorrection(CodeWord_t *cw, int data_size)
{
	return;
}
*/
int thereIsError(CodeWord_t *cw, int data_size)
{
	int i, j, nb_de_un, erreur = 0;
	printf("Les erreurs : ");
	for(i = 0 ; i < data_size ; i++)
	{
		nb_de_un = 0;
		for(j = 1 ; j <= 8 ; j++) 
			if(getNthBit(cw[i],j))
				nb_de_un++;
		if(getNthBit(cw[i], 9) != nb_de_un%2)
		{
			printf("[\033[36m%d\033[00m:\033[31m%c\033[00m] ", i, cw[i]);
			erreur = 1;
		}
	}
	if(! erreur)
		printf("aucune erreur\n");
	else
		printf("\n");
	return erreur;
}

void
decoding (char *cw, int cw_size, char *message, int *data_size)
{
  *data_size = cw_size / sizeof (CodeWord_t);

  //-- For error correction
  //-- to uncomment when complete and needed
  //errorCorrection((CodeWord_t*)cw, *data_size);

  //-- For decoding
  copyDataBitsDecoding ((CodeWord_t *) cw, message, *data_size);

  //-- For error detection
  //-- to uncomment when complete and needed
	if(thereIsError((CodeWord_t*)cw, *data_size))
	{
		printf("PARITY ERROR: \"%s\"\n", message);
	}

	return;
}
