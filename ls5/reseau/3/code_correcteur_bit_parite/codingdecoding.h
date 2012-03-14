/**
 * @file codingdecoding.h
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
 * Headers to generate and decipher the error-correcting code
 */

#ifndef _CODEC_H
#define _CODEC_H

#include "logic.h"

/**
 * Copy data bits in code words.
 *
 * Copy bits of each data word in the right place of code words.
 *
 * @param pointer to data flow
 * @param pointer to code words
 * @param size of the data flow (in bytes)
 *
 * @return nothing (modify directly the code words) 
 */
void copyDataBitsCoding(char *, CodeWord_t *, int);

/**
 * Compute control bits.
 *
 * For each code word, compute and set control bits regarding the
 * Hamming correction-error code.
 *
 * @param pointer to code words
 * @param size of the code words
 *
 * @return nothing (modify directly the code words) 
 */
void computeCtrlBits(CodeWord_t *, int);

/**
 * Coding.
 *
 * First copy data bits then compute control bits
 * for each code word.
 *
 * @param pointer to data flow
 * @param size of data flow (in bytes)
 * @param pointer to code words
 * @param size of code words (in bytes)
 *
 * @return nothing (modify directly the code words)
 */
void coding(char *, int, char *, int *);


/**
 * Get data bits.
 *
 * Get data bits from each code word and store them in a data flow.
 *
 * @param pointer to code words
 * @param pointer to data flow
 * @param size of data flow
 *
 * @return nothing (modify directly the data flow)
 */
void copyDataBitsDecoding(CodeWord_t *, char *, int);


/**
 * Correct errors.
 *
 * Correct errors in each code words regarding to the Hamming
 * error-correction code.
 *
 * @param pointer to code words with potential errors
 * @param size of the data flow
 *
 * @return nothing (modify directly the code words)
 */
void errorCorrection(CodeWord_t *, int);

/**
 * Detect errors.
 *
 * Detect errors in each code words regarding to the polynomial or
 * parity error-detection codes.
 * 
 * @param pointer to code words
 * @param size of the data flow
 *
 * @return 0 if there is no error, 1 otherwise
 */
int thereIsError(CodeWord_t *, int);

/**
 * Decoding the code words.
 *
 * From the code words, extracts the data bits and detects or corrects
 * the potential errors.
 *
 * @param pointer to code words 
 * @param size of code words
 * @param pointer to data flow
 * @param size of the data flow
 *
 * @return nothing (call the other functions)
 */
void decoding(char *, int, char *, int *);

#endif /* _CODEC_H */
