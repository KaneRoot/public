/**
 * @file coding.c
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
 * Generate code words from the initial data flow
 */

#include <stdio.h>
#include "codingdecoding.h"
#include "mesfonctions.h"

void
copyDataBitsCoding (char *message, CodeWord_t * cw, int size)
{
  int i = 0;

  for (i = 0; i < size; i++)
  {
    setNthBitCW (&(cw[i]), 1, getNthBit (message[i], 1));
    setNthBitCW (&(cw[i]), 2, getNthBit (message[i], 2));
    setNthBitCW (&(cw[i]), 3, getNthBit (message[i], 3));
    setNthBitCW (&(cw[i]), 4, getNthBit (message[i], 4));
    setNthBitCW (&(cw[i]), 5, getNthBit (message[i], 5));
    setNthBitCW (&(cw[i]), 6, getNthBit (message[i], 6));
    setNthBitCW (&(cw[i]), 7, getNthBit (message[i], 7));
    setNthBitCW (&(cw[i]), 8, getNthBit (message[i], 8));
  }

  return;
}
matrice_s * get_matrice_cw(CodeWord_t * cw, int offset)
{
	matrice_s * m = create_matrix(1, 4);
	m->matrice[0][0] = getNthBit(cw[0], offset);
	m->matrice[0][1] = getNthBit(cw[0], ++offset);
	m->matrice[0][2] = getNthBit(cw[0], ++offset);
	m->matrice[0][3] = getNthBit(cw[0], ++offset);

	return m;
}
CodeWord_t matrice_to_codeword(matrice_s * m)
{
	CodeWord_t x;
	int i;
	for(i = 0 ; i < m->nbc ; i++)
		setNthBitCW(&x, i + 1, m->matrice[0][i]);
	return x;
}
void computeCtrlBits(CodeWord_t *cw, int size)
{
	matrice_s * m = get_matrice_generatrice();
	matrice_s *tmp1, *tmp2;
	matrice_s *tmp3, *tmp4;
	CodeWord_t cwtmp1, cwtmp2;
	int i;

	/* pour tout cw[i] faire : 
	 * get_matrice_cw 1 et de 5 qu'on multiplie par m
	 * on fait modulo 2 puis on matrice_to_codeword qu'on va placer dans un codeword plus grand
	 */

	for(i = 0 ; i < size ; i++)
	{
		tmp1 = get_matrice_cw(&(cw[i]),1);
		tmp2 = get_matrice_cw(&(cw[i]),5);

//		display_matrix(tmp1);
//		display_matrix(tmp2);

		tmp3 = multiplication_matrices(tmp1, m);
		tmp4 = multiplication_matrices(tmp2, m);
		matrice_mod_2(tmp3);
		matrice_mod_2(tmp4);
		cwtmp1 = matrice_to_codeword(tmp3);
		cwtmp2 = matrice_to_codeword(tmp4);
		cwtmp2 = cwtmp2 << 8;
		cw[i] = cwtmp1 + cwtmp2;

		if(cw[i] != 0)
		{
			printf("cw %d ", i);
			printBits(cw[i], "cw");
		}
		free_matrix(tmp1);
		free_matrix(tmp2);
		free_matrix(tmp3);
		free_matrix(tmp4);
	}

	free_matrix(m);
}

void
coding (char *message, int data_size, char *cw, int *cw_size)
{
  *cw_size = data_size * sizeof (CodeWord_t);

  copyDataBitsCoding (message, (CodeWord_t *) cw, data_size);
  //-- to uncomment when complete and needed
  computeCtrlBits((CodeWord_t*)cw, *cw_size);

  return;
}
