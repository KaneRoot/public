/**
 * @file medium.c
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
 * Main functions for the medium. Implements a non-reliable link.
 */

#include "sockettoolbox.h"
#include "codingdecoding.h"
#include "error.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/**
 * Forward data.
 *
 * Reads s_rec socket and forwards data to s_send socket.
 *
 * @param socket descriptor for receiving data
 * @param socket descriptor to send data
 * @param addr structure to which forwarding data
 * @param error type (see error.h)
 *
 * @return -1 in case of error, 0 if the received frame only includes
 *         one char, 1 otherwise
 */
static int forward(int s_rec,
                   int s_send,
                   struct sockaddr_un send_addr,
                   int error_type)
{
  int nb_rec  = 0;
  int nb_send = 0;

  char cw[MAX_MSG_CODE];
  memset(cw, '\0', MAX_MSG_CODE*sizeof(char));

  struct sockaddr_un remote_rec;
  unsigned int addr_size = sizeof(struct sockaddr_un);

  nb_rec = recvfrom(s_rec, cw, MAX_MSG_CODE, 0,
                    (struct sockaddr *) &remote_rec,
                    &addr_size);

  if(nb_rec < 0)
    {
      perror("read socket");
      return(-1);
    }

  if(nb_rec == 0)
    {
      if(sendto(s_send, "", 0, 0,
		(struct sockaddr*) &send_addr,
		sizeof(struct sockaddr_un)) < 0)
	{
	  perror("sendto \'.\' 1");
	  return(-1);
	}

      return(0);
    }

  else if(nb_rec >= 0)
    {
      includeError(cw, nb_rec, error_type);

      nb_send = sendto(s_send, cw, nb_rec, 0,
		       (struct sockaddr*) &send_addr,
		       sizeof(struct sockaddr_un));

      if(nb_send < 0)
	{
	  perror("sendto");
	  return(-1);
	}
      else
	{
	  return(1);
	}
    }

  return 0;
}

/**
 * Main function.
 *
 * Get messages from the sender and potentially generates errors before
 * forwarding them to the receiver. Implements a non-reliable link.
 *
 * @param the first argument should be the error type. See error.h for
 *        further details
 *
 * @return 0 if the program has successfully completed,
 *         anything else otherwise
 */
int main(int argc, char **argv)
{
  fd_set reading;
  fd_set reading2;

  struct sockaddr_un remote_send;
  struct sockaddr_un remote_rec;

  int s_medsend  = 0;
  int s_medrec   = 0;
  int nbfds      = 0;
  int nb_events  = 0;

  int stop       = 0;
  int crash      = 0;
  int res        = 0;
  int error_type = 0;

  if( (argc != 1) && (argc != 2) )
    {
      printf("Usage : medium\n");
      printf("ou      medium <typederreur> \n");
      exit(1);
    }

  if(argc == 1)
    {
      // no error
      error_type = 0;
    }
  else
    {
      error_type = atoi(argv[1]);
    }

  //-- set the random generator
  srand48(time(0));

  //-- create and bind sockets
  s_medsend = getAndBindSocket("s_medsend");
  s_medrec  = getAndBindSocket("s_medrec");

  //-- set the remote addr
  remote_send = setAddr("sock_send");
  remote_rec  = setAddr("sock_rec");

  //-- set the highest descriptor for select()
  if(s_medsend > s_medrec)
    {
      nbfds = s_medsend + 1;
    }
  else
    {
      nbfds = s_medrec + 1;
    }

      //-- Preparation des ensembles de descripteurs
  FD_ZERO(&reading);
  FD_SET(s_medsend, &reading);
  FD_SET(s_medrec , &reading);

  //-- transfer data
  printf("medium ready\n");

  while( (!stop) && (!crash) )
    {
      //-- works with a copy of the set
      reading2 = reading;

      //-- waits for an event
      nb_events = select(nbfds, &reading2, NULL, NULL, NULL);

      if(nb_events == -1)
	{
	  perror("select");
	  crash = 1;
	}

      //-- if the sender sends a message
      if(FD_ISSET(s_medsend, &reading2))
	{
	  res = forward(s_medsend, s_medrec, remote_rec, error_type);

	  if(res == 0)
	    {
	      stop = 1;
	    }
	  else if(res < 0)
	    {
	      crash = 1;
	    }
	}

      // if the receiver sends a message
      if(FD_ISSET(s_medrec, &reading2))
	{
	  res = forward(s_medrec, s_medsend, remote_send, error_type);

	  if(res == 0)
	    {
	      stop = 1;
	    }
	  else if(res < 0)
	    {
	      crash = 1;
	    }
	}
    }

  if(crash)
    {
      printf("Transfer stopped\n\n");
    }
  else if(stop)
    {
      printf("Transfer complete.\n\n");
    }

  close(s_medrec);
  close(s_medsend);
  remove("s_medsend");
  remove("s_medrec");

  return 0;
}
