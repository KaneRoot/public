/**
 * @file error.h
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
 * Headers to generate errors in frames. Implements a non-reliable link
 * model.
 */

#ifndef _ERROR_H
#define _ERROR_H

#include <stdlib.h>
#include <math.h>

/**
 * Should be between 0 and 1 otherwise acts as if set to 1.
 */
#define ERROR_RATE (1)

/**
 * Get random number.
 * 
 * Generate a random number between [0;1]. See the related to manpage
 * to further details.
 *
 * @param nothing
 * @return a random double set between [0;1]
 */
//extern double drand48(void);


/**
 * Include errors in code words.
 *
 * Call one of the includeError1, 2, 3 or 4 functions.
 *
 * @param pointer on the first code word
 * @param size of the entire data flow
 * @param error type: e.g. 1 for includeError1() function
 *
 * @return nothing (modify directely each code word)
 */
void includeError(char *, int, int);

/**
 * Include errors in code words (1).
 *
 * Randomly turns a bit on or off in each 2 bytes code word.
 * Note: if we turn more than one bit per char, we have more than
 * one error per code word and therefore Hamming becomes useless.
 *
 * @param pointer on the first code word
 * @param size of the entire data flow
 *
 * @return nothing (modify directely each code word)
 */
void includeError1(char *, int);

/**
 * Include errors in code words (2).
 *
 * If ERROR_RATE=1, then acts as includeError1 function. 
 * If ERROR_RATE=0, then do not change anything.
 * Between these values, all intermediate situations are possible.
 *
 * @param pointer on the first code word
 * @param size of the entire data flow
 *
 * @return nothing (modify directely each code word)
 */
void includeError2(char *, int);

/**
 * Include errors in code words (3).
 *
 * Change a single char in the entire data flow.
 *
 * @param pointer on the first code word
 * @param size of the entire data flow
 *
 * @return nothing (modify directely each code word)
 */
void includeError3(char *, int);

/**
 * Include errors in code words (4).
 *
 * If ERROR_RATE=1, then changes all char in the entire data flow.
 * If ERROR_RATE=0, then do not change anything.
 * Between these values, all intermediate situations are possible.
 *
 * @param pointer on the first code word
 * @param size of the entire data flow
 *
 * @return nothing (modify directely each code word)
 */
void includeError4(char *, int);

#endif
