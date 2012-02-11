#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int sockfd;
    socklen_t addrlen;
    struct sockaddr_in6 dest;

    if(argc != 4)
    {
        printf("USAGE: %s @dest port_num string\n", argv[0]);
        exit(-1);
    }

    if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
	    exit(EXIT_FAILURE);
    }

    dest.sin6_family = AF_INET6;
    dest.sin6_port   = htons(atoi(argv[2]));
    addrlen         = sizeof(struct sockaddr_in6);

    if(inet_pton(AF_INET6, argv[1], &dest.sin6_addr) != 1)
    {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // send string
    if(sendto(sockfd, argv[3], sizeof(char)* strlen(argv[3]), 
				0, (struct sockaddr*) &dest, addrlen) == -1)
    {
        perror("sendto");
	    close(sockfd);
	    exit(EXIT_FAILURE);
    }

    // close the socket
    close(sockfd);

    return 0;
}
