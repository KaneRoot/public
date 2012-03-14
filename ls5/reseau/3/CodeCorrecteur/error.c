/**
 * @file error.c
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
 * Functions to generate errors in frames. Implements a non-reliable
 * link model: either bit errors or char errors.
 */

#include "error.h"
#include "logic.h"
#include <stdio.h>

void includeError(char *string, int size, int error_type)
{
  switch(error_type)
    {
      case 0: break; //-- no error
      case 1: includeError1(string, size); break;
      case 2: includeError2(string, size); break;
      case 3: includeError3(string, size); break;
      case 4: includeError4(string, size); break;
      default:
        {
	  printf("%d: unknown error type\n", error_type);
	  exit(1);
	}
    }

  return;
}

void includeError1(char *string, int size)
{
  int i              = 0;
  int exponent       = 0;
  unsigned char mask = '\0';

  for(i=0; i<size; i+=2)
    {
      exponent = floor(drand48() * 16);

      if(exponent < 8)
	{
	  mask = 1 << exponent;
	  string[i] = xor(string[i], mask);
	}
      else
	{
	  mask = 1 << (exponent-8);
	  string[i+1] = xor(string[i+1], mask);
	}
    }

  return;
}

void includeError2(char *string, int size)
{
  int i              = 0;
  int exponent       = 0;
  unsigned char mask = '\0';

  for(i=0; i<size; i++)
    {
      if(drand48() < ERROR_RATE)
	{
	  exponent = floor(drand48() * 16);

	  if(exponent < 8)
	    {
	      mask = 1 << exponent;
	      string[i] = xor(string[i], mask);
	    }
	  else
	    {
	      mask = 1 << (exponent-8);
	      string[i+1] = xor(string[i+1], mask);
	    }
	}
    }

  return;
}

void includeError3(char *string, int size)
{
  int index  = 0;
  int offset = 0;

  index  = floor(drand48() * size);
  offset = floor(drand48() * 256);
  string[index] = (string[index] + offset) % 256;

  return;
}

void includeError4(char *string, int size)
{
  int i      = 0;
  int offset = 0;

  for(i=0; i<size; i++)
    {
      if(drand48() < ERROR_RATE)
	{
	  offset    = floor(drand48() * 256);
	  string[i] = (string[i] + offset) % 256;
	}
    }

  return;
}
