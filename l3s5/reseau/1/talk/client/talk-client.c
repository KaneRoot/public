#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "talk-client.h"
#define TAILLE_BUF 1024

int sockfd;
struct sockaddr_in6 server;
socklen_t addrlen;
fd_set masterfds, readfds;

int main(int argc, char **argv)
{
	char buf[TAILLE_BUF];
	int i, rt;

	init_programme(argc, argv);

	FD_SET(0, &masterfds);		// On écoute sur l'entrée standard
	FD_SET(sockfd, &masterfds); // On ajoute le socket ouvert
	while(1)
	{
		memcpy(&readfds, &masterfds, sizeof(fd_set));
		rt = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
		if(rt < 0)
			quitter("select");

		for(i = 0 ; i < FD_SETSIZE ; i++)
		{
			if(FD_ISSET(i, &readfds))
			{
				// send string
				if(i == 0)
					envoyer_donnee();
				else
				{
					printf("%d fait partie des fds -- on reçoit une donnée\n",i);
					rt = recv(sockfd, buf, TAILLE_BUF, 0);
					if(rt < 0)
						quitter("recv");
					else if(rt == 0)
						sortie_programme();
					else
						printf("On reçoit : %s\n", buf);
				}
			}
		}

	}

    // close the socket
    close(sockfd);

    return 0;
}
void sortie_programme(void)
{
	clore_les_sockets();
	printf("Le serveur a fermé sa socket, fin de programme\n");
	exit(EXIT_SUCCESS);
}
void init_programme(int argc, char *argv[])
{
    // check the number of args on command line
    if(argc != 3)
    {
        printf("USAGE: %s @server port_num\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // socket factory
    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
	    exit(EXIT_FAILURE);
    }

    // init remote addr structure and other params
    server.sin6_family = AF_INET6;
	server.sin6_port   = htons(atoi(argv[2]));
    addrlen           = sizeof(struct sockaddr_in6);

    // get addr from command line and convert it
    if(inet_pton(AF_INET6, argv[1], &server.sin6_addr) != 1)
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

	FD_ZERO(&masterfds);
    printf("Connection OK\n");
}

int plus_grand_fd(void)
{
	return sockfd;
}

void quitter(char * erreur)
{
	perror(erreur);
	clore_les_sockets();
	exit(EXIT_FAILURE);
}

void clore_les_sockets(void)
{
	close(sockfd);
}
void envoyer_donnee(void)
{
	int rt;
	char buf[TAILLE_BUF];

	rt = read(0, buf, TAILLE_BUF);
	if(rt <= 0)
		quitter("read");

	rt = sendto(sockfd, buf, TAILLE_BUF, 0, (struct sockaddr *) &server, addrlen);
	if(rt == -1)
		quitter("sendto");
}
