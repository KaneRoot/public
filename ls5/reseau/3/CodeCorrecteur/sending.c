/**
 * @file sending.c
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
 * Main functions for the sender.
 */

#include "sockettoolbox.h"
#include "codingdecoding.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

/**
 * Send code words through a UNIX socket.
 *
 * From the original data flow generates code words and sends them.
 *
 * @param UNIX socket descriptor
 * @param pointer to original data flow
 * @param size of data flow
 * @param remote addr structure
 *
 * @return nothing (coding and sending message)
 */
static void sendMessage(int desc,
			char *message,
			int size,
			struct sockaddr_un remote_addr)
{
  int ok      = 0;
  int res     = 0;
  int cw_size = 0;

  char cw[MAX_MSG_CODE];
  memset(cw, '\0', MAX_MSG_CODE*sizeof(char));

  coding(message, size, cw, &cw_size);

  do
    {
      res = sendto(desc, cw, cw_size, 0,
		   (struct sockaddr*) &remote_addr,
		   sizeof(struct sockaddr_un));

      if(res < 0 && errno == ENOBUFS)
	{
	  usleep(1000);
	  ok = 0;
	}
      else
	{
	  ok = 1;
	}
    }
  while(!ok);

  if(res == -1)
    {
      perror("sendto sender\n");
      exit(1);
    }

  return;
}

/**
 * Disconnect socket.
 *
 * Sends an empty message to complete the transmission.
 *
 * @param UNIX socket descriptor
 * @param remote addr structure
 *
 * @return nothing
 */
static void disconnectRequest(int desc, struct sockaddr_un remote_addr)
{
  int res = 0;

  res = sendto(desc, "", 0, 0,
	       (struct sockaddr*) &remote_addr,
	       sizeof(struct sockaddr_un));

  if(res == -1)
    {
      perror("sendto deconnect\n");
      exit(1);
    }

  return;
}

/**
 * Main function.
 *
 * @param the first argument should be the filename to send
 *
 * @return 0 if the program has successfully completed,
 *         anything else otherwise
 */
int main(int argc, char **argv)
{
  int readFile = 0;
  int size     = 0;
  int desc     = 0;

  struct sockaddr_un remote_addr;

  mode_t mode = 0;

  char message[MAX_MESSAGE];
  memset(message, '\0', MAX_MESSAGE*sizeof(char));

  if(argc != 2)
    {
      printf("Usage : sender FileToSend \n");
      exit(1);
    }

  //-- open the file in read mode
  mode = S_IRUSR|S_IWUSR;

  if((readFile = open(argv[1], O_RDONLY, mode)) == -1)
    {
      perror(argv[1]);
      exit(1);
    }

  //-- create and bind local socket
  //-- and set the remote addr structure
  desc        = getAndBindSocket("sock_send");
  remote_addr = setAddr("s_medsend");

  //-- transmission
  while((size = read(readFile, message, MAX_MESSAGE)) > 0)
    {
      sendMessage(desc, message, size, remote_addr);
    }

  //-- end of transmission
  if(size < 0)
    {
      perror("read");
      exit(1);
    }
  else //-- size = 0
    {
      printf("Transmission complete\n");
      disconnectRequest(desc, remote_addr);
      close(desc);
      close(readFile);
      remove("sock_send");
    }

  return 0;
}
