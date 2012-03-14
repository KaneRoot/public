/**
 * @file sockettoolbox.h
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
 * Headers to configure a socket and related to addr.
 */

#ifndef _SOCKETTOOLBOX_H
#define _SOCKETTOOLBOX_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <fcntl.h>

#ifdef __linux__
#include <sys/ioctl.h>
#endif

#ifdef __sun__
#include <sys/filio.h>
#endif

#ifdef __sgi
#include <sys/filio.h>
#include <stdlib.h>
#endif

/**
 * Set UNIX address.
 *
 * Set a UNIX sockaddr structure from a pathname.
 *
 * @param pointer to the pathname string
 *
 * @return the UNIX sockaddr structure
 */
extern struct sockaddr_un setAddr(char *);


/**
 * Get and bind a UNIX socket.
 *
 * Create a UNIX socket and bind it with the pathname.
 *
 * @param pointer to the pathname string
 *
 * @return socket descriptor
 */
extern int getAndBindSocket(char *);

#endif
