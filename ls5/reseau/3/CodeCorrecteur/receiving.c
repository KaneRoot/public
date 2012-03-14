/**
 * @file receiving.c
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
 * Main functions for the receiver.
 */

#include <unistd.h>
#include <stdlib.h>
#include "sockettoolbox.h"
#include "codingdecoding.h"

/**
 * Receive code words through a UNIX socket.
 *
 * From the code words, retrieve the original data flow.
 *
 * @param UNIX socket descriptor
 * @param pointer to data flow
 *
 * @return -1 in case of error, the size (in bytes) of data flow otherwise
 */
static int receiveMessage(int desc, char *message)
{
  static int stop = 0;
  int cw_size     = 0;
  int data_size   = 0;

  char cw[MAX_MSG_CODE];
  memset(cw, '\0', MAX_MSG_CODE*sizeof(char));

  struct sockaddr_un remote_addr;
  unsigned int addr_size = sizeof(struct sockaddr_un);

  if(stop)
    {
      return(0);
    }
  else
    {
      cw_size = recvfrom(desc, cw, MAX_MSG_CODE, 0,
			 (struct sockaddr *) &remote_addr,
			 &addr_size);

      if(cw_size == 0)
	{
	  return(0);
	}
      else if(cw_size > 0)
	{
	  decoding(cw, cw_size, message, &data_size);
	  return(data_size);
	}

      return(-1);
    }
}

/**
 * Main function.
 *
 * @param the first argument should be the filename to write within
 *
 * @return 0 if the program has successfully completed,
 *         anything else otherwise
 */
int main(int argc, char **argv)
{
  int saveFile = 0;
  int size     = 0;
  int res      = 0;
  int desc     = 0;
  int stop     = 0;

  mode_t mode  = 0;

  char message[MAX_MESSAGE];
  memset(message, '\0', MAX_MESSAGE*sizeof(char));

  if(argc != 2)
    {
      printf("Usage: receiver FileReceived \n");
      exit(1);
    }

  //-- open the file in write mode
  mode = S_IRUSR|S_IWUSR;

  if((saveFile = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, mode)) == -1)
    {
      perror(argv[1]);
      exit(1);
    }

  //-- create and bind local socket
  desc = getAndBindSocket("sock_rec");

  //-- transmission
  printf("Ready to receive.\n");

  do
    {
      size = receiveMessage(desc, message);

      if(size < 0)
	{
	  perror("reception socket\n");
	  exit(1);
	}
      else if(size > 0)
	{
	  res = write(saveFile, message, size);

	  if(res == -1)
	    {
	      perror("writing receiver\n");
	      exit(1);
	    }
	}
      else if(size == 0)
	{
	  stop = 1;
	}
    }
  while(!stop);

  //-- transmission complete

  printf("Reception complete\n");
  close(desc);
  close(saveFile);
  remove("sock_rec");

  return 0;
}
