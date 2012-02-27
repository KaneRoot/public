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
char buf[TAILLE_BUF];

int main(int argc, char **argv)
{
	int i, rt;

	init_programme(argc, argv);

	FD_SET(0, &masterfds);		// On écoute sur l'entrée standard
	FD_SET(sockfd, &masterfds); // On ajoute le socket lié au serveur
	while(1)
	{
		memcpy(&readfds, &masterfds, sizeof(fd_set));
		bzero(buf, TAILLE_BUF); // On vide le tampon

		rt = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
		if(rt < 0)
			quitter("select");

		for(i = 0 ; i < FD_SETSIZE ; i++)
		{
			if(FD_ISSET(i, &readfds))
			{
				if(i == 0)	// lecture entrée standard + envoi
					envoyer_donnee();
				else		// lecture socket liée au serveur + écriture
					recevoir_donnee();
			}
		}

	}

	// fermer les sockets
	clore_les_sockets();

    return EXIT_FAILURE;
}
void sortie_programme(void)
{
	clore_les_sockets();
	printf("Fin du programme. "
			"Le serveur a fermé sa socket ou vous avez entré ^D.\n");
	exit(EXIT_SUCCESS);
}
void init_programme(int argc, char *argv[])
{
    // check the number of args on command line
    if(argc != 3)
    {
        printf("USAGE: %s @server port_num\n\tExemple: %s ::1 9000\n", argv[0], argv[0]);
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
    if(inet_pton(AF_INET6, argv[1], &server.sin6_addr) < 0)
    {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if(connect(sockfd, (struct sockaddr *) &server, addrlen) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

	FD_ZERO(&masterfds);
	printf(	"Début du programme.\n"
			"\033[36m Pour quitter : ^D \033[00m \n");
}

void quitter(char * erreur)
{
	perror(erreur);
	clore_les_sockets();
	exit(EXIT_FAILURE);
}

void clore_les_sockets(void)
{
	// Qu'un socket à fermer.
	close(sockfd);
}
void envoyer_donnee(void)
{
	int rt;

	rt = read(0, buf, TAILLE_BUF);
	if(rt < 0)
		quitter("read");
	else if(rt == 0)
		sortie_programme();

	rt = sendto(sockfd, buf, TAILLE_BUF, 0, (struct sockaddr *) &server, addrlen);
	if(rt == -1)
		quitter("sendto");

	// On vide le tampon
	fflush(stdin);
}
void recevoir_donnee(void)
{
	int rt;

	rt = recv(sockfd, buf, TAILLE_BUF, 0);
	if(rt < 0)
		quitter("recv");
	else if(rt == 0)
		sortie_programme();
	else
		printf("\033[31m On reçoit :\033[00m %s", buf);
}
