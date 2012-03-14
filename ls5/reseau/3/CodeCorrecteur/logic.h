/**
 * @file logic.h
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
 * Headers for several basic logical functions such as XOR
 */

#ifndef _LOGIC_H
#define _LOGIC_H

#define MAX_MESSAGE 50
#define MAX_MSG_CODE 100

//-- code word type
typedef short CodeWord_t;


/**
 * Get nth bit.

 * Get the value of the nth bit in a number.
 *
 * @param number to extract the bit from
 * @param bit order in the number
 *
 * @return the requested bit set in a char
 */
char getNthBit(int, int);


/**
 * Print bits.
 *
 * Print all bits from a code word.
 * Note: code word size =  2 bytes.
 *
 * @param the code word to pring
 * @param a pointer to a string shown as a comment
 *
 * @return nothing (print only)
 */
void printBits(CodeWord_t, char *);


/**
 * Set a bit in a code word.
 *
 * Change the nth bit of a code word to a certain value.
 *
 * @param pointer to the code word
 * @param bit order
 * @param value to which the bit will be set (0 or 1)
 *
 * @return nothing (modify directely the code word)
 */
void setNthBitCW(CodeWord_t *, int, int);


/**
 * Set a bit in a word.
 *
 * Change the nth bit of a word to a certain value.
 *
 * @param pointer to the word
 * @param bit order
 * @param value to which the bit will be set (0 or 1)
 *
 * @return nothing (modify directely the word)
 */
void setNthBitW(char *, int, int);


/**
 * XOR
 *
 * Make a XOR between two code words.
 *
 * @param the first code word
 * @param the second code word
 *
 * @return result of xor between the two code words
 */
CodeWord_t xor(CodeWord_t, CodeWord_t);


/**
 * Change nth bit.
 *
 * Turns on or off the nth bit of a code word.
 *
 * @param pointer to the code word
 * @param bit order
 *
 * @result nothing (modify directely the code word)
 */
void changeNthBitCW(CodeWord_t *, int);


/**
 * Change nth bit.
 *
 * Turns on or off the nth bit of a word.
 *
 * @param pointer to the word
 * @param bit order
 *
 * @result nothing (modify directely the word)
 */
void changeNthBitW(char *, int);


/**
 * Trunc bits.
 *
 * Turn off all bits which are strictly most significant than a the
 * bit pointed by the bit order param.
 * Would be useful when calculate the degree or the rest of a code
 * word.
 *
 * @param pointer to the code word
 * @param bit order
 *
 * @return nothing (modify directly the code word)
 */
void truncNbits(CodeWord_t *, int);


/**
 * Get degree.

 * Get the degree of a code word.
 * For example, if the code word is set to 10011 then the returned
 * degree will be 4.
 *
 * @param the code word
 *
 * @return the degree of the code word
 */
int getDegree(CodeWord_t);

#endif
