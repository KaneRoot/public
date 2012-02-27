#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LISTEN_BACKLOG 100
#define TAILLE_BUFFER 1024

int main(int argc, char **argv)
{
    int sockfd, sockfd2;
    socklen_t addrlen;
    char buf[TAILLE_BUFFER];

    struct sockaddr_in6 my_addr;
    struct sockaddr_in6 client;

    if(argc != 2)
    {
        printf("USAGE: %s port_num\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1)
    {
		perror("socket");
	    exit(EXIT_FAILURE);
    }

    my_addr.sin6_family		= AF_INET6;
    my_addr.sin6_port        = htons(atoi(argv[1]));
	my_addr.sin6_addr = in6addr_any;
    addrlen                 = sizeof(struct sockaddr_in6);
    memset(buf,'\0',TAILLE_BUFFER);

    if(bind(sockfd, (struct sockaddr *)&my_addr, addrlen) == -1)
    {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

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

    printf("Connexion active\n");
    if(recv(sockfd2, buf, TAILLE_BUFFER, 0) == -1)
    {
        perror("recv");
        close(sockfd);
        close(sockfd2);
        exit(EXIT_FAILURE);
    }

    printf("Message reçu : %s\n", buf);

    close(sockfd);
    close(sockfd2);

    return 0;
}
