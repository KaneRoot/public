/**
 * @file server-tcp.c
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
 * Simple program that creates an IPv4 TCP socket waits for the
 * connection of a client and the reception of a string from that
 * client. The program takes a single parameter which is the local
 * communication port. The IPv4 addr associated to the socket will be
 * all available addr on the host (use INADDR_ANY maccro).
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LISTEN_BACKLOG 100

int main(int argc, char **argv)
{
    int sockfd, sockfd2;
    socklen_t addrlen;
    char buf[1024];

    struct sockaddr_in my_addr;
    struct sockaddr_in client;

    // check the number of args on command line
    if(argc != 2)
    {
        printf("USAGE: %s port_num\n", argv[0]);
        exit(-1);
    }

    // socket factory
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
		perror("socket");
	    exit(EXIT_FAILURE);
    }

    // init local addr structure and other params
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(atoi(argv[1]));
	my_addr.sin_addr.s_addr = htons(INADDR_ANY);;
    addrlen                 = sizeof(struct sockaddr_in);
    memset(buf,'\0',1024);

    // bind addr structure with socket
    if(bind(sockfd, (struct sockaddr *)&my_addr, addrlen) == -1)
    {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // set the socket in passive mode (only used for accept())
    // and set the list size for pending connection
    if(listen(sockfd, LISTEN_BACKLOG) == -1)
    {
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for incomming connection\n");

    if((sockfd2 = accept(sockfd, (struct sockaddr *) &client, &addrlen)) == -1)
    {
        perror("accept");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connection active\n");

    // reception de la chaine de caracteres
    if(recv(sockfd, buf, 1024, 0) == -1)
    {
        perror("recv");
        close(sockfd);
        close(sockfd2);
        exit(EXIT_FAILURE);
    }

    // print the received char
    printf("Message reçu : %s\n", buf);

    // fermeture des sockets
    close(sockfd);
    close(sockfd2);

    return 0;
}
