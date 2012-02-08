/**
 * @file receiver-udp.c
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
 * Simple program that creates an IPv4 UDP socket and waits for the
 * reception of a string. The program takes a single parameter which
 * is the local communication port. The IPv4 addr associated to the
 * socket will be all available addr on the host (use INADDR_ANY
 * maccro).
 */

int main(int argc, char **argv)
{
    int sockfd;
    char buf[1024];
    socklen_t addrlen;

    struct sockaddr_in my_addr;
    struct sockaddr_in client;

    // check the number of args on command line
    if(argc != 2)
    {
        printf("Usage: %s local_port\n", argv[0]);
        exit(-1);
    }

    // socket factory
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // init local addr structure and other params
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(atoi(argv[1]));
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addrlen                 = sizeof(struct sockaddr_in);
    memset(buf,'\0',1024);

    // bind addr structure with socket
    if(bind(sockfd, ) == -1)
    {
        perror(...);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // reception de la chaine de caracteres
    if(recvfrom(...) == -1)
    {
        perror(...);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // print the received char
    printf(...);

    // close the socket
    close(sockfd);

    return 0;
}
