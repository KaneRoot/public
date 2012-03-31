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

matrice_s * get_matrice_generatrice(void)
{
	matrice_s * m;
	m = create_matrix(4, 8);

	m->matrice[0][0] = 1;
	m->matrice[1][1] = 1;
	m->matrice[2][2] = 1;
	m->matrice[3][3] = 1;

	m->matrice[1][4] = 1;
	m->matrice[2][4] = 1;
	m->matrice[3][4] = 1;
	m->matrice[0][5] = 1;
	m->matrice[2][5] = 1;
	m->matrice[3][5] = 1;
	m->matrice[0][6] = 1;
	m->matrice[1][6] = 1;
	m->matrice[3][6] = 1;
	m->matrice[0][7] = 1;
	m->matrice[1][7] = 1;
	m->matrice[2][7] = 1;
	display_matrix(m);

	return m;
}
void matrice_mod_2(matrice_s * m)
{
	int i, j;
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			while(m->matrice[i][j] >= 2)
				m->matrice[i][j] -= 2;
}
void computeCtrlBits(CodeWord_t *cw, int size)
{
//	int i, j;
//	for(i = 0 ; i < size ; i++)
//	{
//	}

	size = 0;
	size = size;

	matrice_s * m = get_matrice_generatrice();
	matrice_s * bla = get_matrice_cw(cw,1);
	matrice_s * bla2 = get_matrice_cw(cw,4);

	matrice_s *tmp1, *tmp2;

	tmp1 = multiplication_matrices(bla, m);
	tmp2 = multiplication_matrices(bla2, m);

	display_matrix(tmp1);
	display_matrix(tmp2);

	matrice_mod_2(tmp1);
	matrice_mod_2(tmp2);

	display_matrix(tmp1);
	display_matrix(tmp2);

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
