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
    struct sockaddr_in server;
	socklen_t addrlen;

    if(argc != 4)
    {
        printf("USAGE: %s @server port_num string\n", argv[0]);
        exit(-1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
	    exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
	server.sin_port   = htons(atoi(argv[2]));
    addrlen           = sizeof(struct sockaddr_in);

    // get addr from command line and convert it
    if(inet_pton(AF_INET, argv[1], &server.sin_addr) != 1)
    {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Trying to connect to the remote host\n");
    if(connect(sockfd, (struct sockaddr *) &server, addrlen) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connection OK\n");

    // send string
    if(sendto(sockfd, argv[3], sizeof(char) * strlen(argv[3]),
				0,
				(struct sockaddr *) &server,
				addrlen) == -1)
    {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Disconnection\n");

    // close the socket
    close(sockfd);

    return 0;
}
