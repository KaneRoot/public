/**
 * @file client-tcp.c
 * @author Julien Montavont
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Simple program that creates an IPv4 TCP socket and tries to connect
 * to a remote host before sending a string to this host. The string,
 * IPv4 addr and port number of the remote host are passed as command
 * line parameters as follow:
 * ./pg_name IPv4_addr port_number string
 */

#include ...

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in server;

    // check the number of args on command line
    if(argc != 4)
    {
        printf("USAGE: %s @server port_num string\n", argv[0]);
        exit(-1);
    }

    // socket factory
    if((sockfd = socket(...)) == -1)
    {
        perror(...);
	    exit(EXIT_FAILURE);
    }

    // init remote addr structure and other params
    server.sin_family = ...;
    server.sin_port   = ...;
    addrlen           = sizeof(struct sockaddr_in);

    // get addr from command line and convert it
    if(inet_pton(...) != 1)
    {
        perror(...);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Trying to connect to the remote host\n");
    if(connect(...) == -1)
    {
        perror(...);
        exit(EXIT_FAILURE);
    }

    printf("Connection OK\n");

    // send string
    if(sendto(...) == -1)
    {
        perror(...);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Disconnection\n");

    // close the socket
    close(sockfd);

    return 0;
}
