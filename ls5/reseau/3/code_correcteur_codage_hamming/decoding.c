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
#include "mesfonctions.h"

matrice_s * get_matrice_cw_long(CodeWord_t x)
{
	matrice_s * m = create_matrix(1, 8);
	int i;
	for(i = 0 ; i < 8 ; i++)
		m->matrice[0][i] = getNthBit(x, i+1);

	return m;
}

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

int ajouter_puissance_deux(int n)
{
	int x = 2;
	if(n <= 0)
		return 1;

	while(--n >= 1)
		x *= 2;

	return x;
}
int matrice_to_int(matrice_s * m)
{
	int nombre = 0, i;
	for(i = 0 ; i < 4 ; i++)
		nombre = (m->matrice[i][0] != 0.0) ? nombre + ajouter_puissance_deux(i) : nombre;
	return nombre;
}
void errorCorrection(CodeWord_t *cw, int data_size)
{
	matrice_s * m = get_matrice_parite();
	matrice_s *tmp1, *tmp2;
	matrice_s *tmp3, *tmp4;
	matrice_s *tr1, *tr2;
	CodeWord_t tmp;
	int i, j, err1, err2;

	for(i = 0 ; i < data_size ; i++)
	{
//		printf("cw %d ", i);
//		printBits(cw[i], "cw");
		tmp1 = get_matrice_cw_long(cw[i]);
		cw[i] = cw[i] >> 8;
		tmp2 = get_matrice_cw_long(cw[i]);
	
		tr1 = transposee_matrix(tmp1);
		tr2 = transposee_matrix(tmp2);

		tmp3 = multiplication_matrices(m, tr1);
		tmp4 = multiplication_matrices(m, tr2);

		matrice_mod_2(tmp3);
		matrice_mod_2(tmp4);

		err1 = matrice_to_int(tmp3);
		err2 = matrice_to_int(tmp4);

//		printf("Nombre 1 = %d  Nombre 2 : %d\n", err1, err2);

		for( j = 0 ; j < 4 ; j++)
			if( err1 != 0 && (j + 1) == err1)
				setNthBitCW(&tmp, j + 1, ((int) tmp1->matrice[0][j] + 1) % 2);
			else
				setNthBitCW(&tmp, j + 1, tmp1->matrice[0][j]);

		for( j = 0 ; j < 4 ; j++)
			if( err2 != 0 && (j + 1) == err2)
				setNthBitCW(&tmp, j + 5, ( (int ) tmp2->matrice[0][j] + 1) % 2);
			else
				setNthBitCW(&tmp, j + 5, tmp2->matrice[0][j]);

		cw[i] = tmp;

		free_matrix(tmp1);
		free_matrix(tmp2);
		free_matrix(tmp3);
		free_matrix(tmp4);
		free_matrix(tr1);
		free_matrix(tr2);
	}

	free_matrix(m);
	return;
}
int thereIsError(CodeWord_t *cw, int data_size)
{
	matrice_s * m = get_matrice_parite();
	matrice_s *tmp1, *tmp2;
	matrice_s *tmp3, *tmp4;
	matrice_s *tr1, *tr2;
	CodeWord_t tmp;
	int i, err1, err2;

	for(i = 0 ; i < data_size ; i++)
	{
		tmp1 = get_matrice_cw_long(cw[i]);
		tmp = cw[i] >> 8;
		tmp2 = get_matrice_cw_long(tmp);
	
		tr1 = transposee_matrix(tmp1);
		tr2 = transposee_matrix(tmp2);

		tmp3 = multiplication_matrices(m, tr1);
		tmp4 = multiplication_matrices(m, tr2);

		matrice_mod_2(tmp3);
		matrice_mod_2(tmp4);

		err1 = matrice_to_int(tmp3);
		err2 = matrice_to_int(tmp4);
		if(err1 != 0 || err2 != 0)
		{
			free_matrix(tmp1);
			free_matrix(tmp2);
			free_matrix(tmp3);
			free_matrix(tmp4);
			free_matrix(tr1);
			free_matrix(tr2);
			free_matrix(m);
			return 1;
		}
		free_matrix(tmp1);
		free_matrix(tmp2);
		free_matrix(tmp3);
		free_matrix(tmp4);
		free_matrix(tr1);
		free_matrix(tr2);
	}

	free_matrix(m);
	return 0;
}

void
decoding (char *cw, int cw_size, char *message, int *data_size)
{
  *data_size = cw_size / sizeof (CodeWord_t);

  //-- For error detection
  //-- to uncomment when complete and needed
	if(thereIsError((CodeWord_t*)cw, *data_size))
	{
		printf("PARITY ERROR\n");
	}

  //-- For error correction
  //-- to uncomment when complete and needed
  errorCorrection((CodeWord_t*)cw, *data_size);

  //-- For decoding
  copyDataBitsDecoding ((CodeWord_t *) cw, message, *data_size);

	return;
}
