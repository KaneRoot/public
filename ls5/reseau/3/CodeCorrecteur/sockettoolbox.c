/**
 * @file sockettoolbox.c
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
 * Configure a socket and the related to addr.
 */

#include <stdlib.h>
#include "sockettoolbox.h"

struct sockaddr_un setAddr(char *ref)
{
  struct sockaddr_un remote_addr;

  remote_addr.sun_family = AF_UNIX;
  strcpy(remote_addr.sun_path, ref);

  return(remote_addr);
}

int getAndBindSocket(char *ref)
{
  int desc = 0;
  int res  = 0;
  struct sockaddr_un local_addr;

  desc = socket(AF_UNIX, SOCK_DGRAM, 0);

  if(desc == -1)
    {
      perror("socket");
      exit(1);
    }

  local_addr.sun_family = AF_UNIX;
  strcpy(local_addr.sun_path, ref);

  res = bind(desc, (struct sockaddr*) &local_addr, sizeof(local_addr));

  if(res == -1)
    {
      perror(ref);
      exit(1);
    }

  return(desc);
}
