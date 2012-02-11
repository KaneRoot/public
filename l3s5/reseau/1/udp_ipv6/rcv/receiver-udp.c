#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAILLE_BUFFER 1024

int main(int argc, char **argv)
{
    int sockfd;
    char buf[TAILLE_BUFFER];
    socklen_t addrlen;

    struct sockaddr_in6 my_addr;

    if(argc != 2)
    {
        printf("Usage: %s local_port\n", argv[0]);
        exit(-1);
    }

    if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    my_addr.sin6_family     = AF_INET6;
    my_addr.sin6_port       = htons(atoi(argv[1]));
    my_addr.sin6_addr		= in6addr_any;
    addrlen                 = sizeof(struct sockaddr_in6);
    memset(buf,'\0',TAILLE_BUFFER);

    if(bind(sockfd, (struct sockaddr *) &my_addr, addrlen ) == -1)
    {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // reception de la chaine de caracteres
    if(recvfrom(sockfd, buf, TAILLE_BUFFER, 0, NULL, NULL) == -1)
    {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // print the received char
    printf("Message reçu : %s\n", buf);

    // close the socket
    close(sockfd);

    return 0;
}
