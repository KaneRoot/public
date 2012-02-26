#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "talk-server.h"


#define LISTEN_BACKLOG 10
#define TAILLE_BUFFER 1024
#define NB_CLIENTS 10

int sockfd;
char buf[TAILLE_BUFFER];
socklen_t addrlen;
client_s client[NB_CLIENTS];
fd_set readfds, masterfds;

int main(int argc, char **argv)
{
	int i, rt, plusgrandfd; // rt = return value

	init_programme(argc,argv);

	// Au cas où on veuille quitter (^D)
	FD_SET(0, &masterfds);
	FD_SET(sockfd, &masterfds);

	// On ne quitte pas cette boucle sauf pour terminer le programme
	while(1) 
	{
		memcpy(&readfds, &masterfds, sizeof(fd_set));
		bzero(buf, TAILLE_BUFFER); // On vide le tampon

		plusgrandfd = plus_grand_fd();
		rt = select(plusgrandfd + 1, &readfds, NULL, NULL, NULL);

		if(rt < 0)
			printf("retour select : %d \n", rt);

		for(i = 0 ; i <= plusgrandfd ; i++)
		{
			if(FD_ISSET(i, &readfds))
			{
				if(i == sockfd)		// connexion entrante
					attendre_utilisateur();
				else if(i == 0)
					sortie_programme();
				else if(i >= 4 && i < NB_CLIENTS + 4)	// utilisateurs
					recevoir_utilisateur(i - 4);
			}
		}
	}

	// On ne devait pas sortir de la boucle
	clore_les_sockets();
    return EXIT_FAILURE;
}

void quitter(char * erreur)
{
	perror(erreur);
	clore_les_sockets();
	exit(EXIT_FAILURE);
}

void init_programme(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("USAGE: %s port_num\n\tExemple : %s 9000\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 my_addr;

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1)
		quitter("socket");

    my_addr.sin6_family		= AF_INET6;
    my_addr.sin6_port       = htons(atoi(argv[1]));
	my_addr.sin6_addr		= in6addr_any;
    addrlen                 = sizeof(struct sockaddr_in6);
    memset(buf,'\0',TAILLE_BUFFER);

    if(bind(sockfd, (struct sockaddr *)&my_addr, addrlen) == -1)
    {
        close(sockfd);
		quitter("bind");
    }

    if(listen(sockfd, LISTEN_BACKLOG) == -1)
    {
        close(sockfd);
		quitter("listen");
    }
	FD_ZERO(&masterfds);

	printf( "Début du programme.\n"
			"\033[36m Pour quitter : ^D\033[00m \n");
}
void attendre_utilisateur(void)
{
	int i;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(client[i].fd <= 0)
			break;
    if((client[i].fd = accept(sockfd, (struct sockaddr *) &client[i].adr, &addrlen)) == -1)
		quitter("accept");

	FD_SET(client[i].fd, &masterfds);
	printf("Connexion à l'emplacement %d\n", i);
}
int plus_grand_fd(void)
{
	int i, max = -1;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(client[i].fd > max)
			max = client[i].fd;
	max = (max > sockfd) ? max : sockfd;
	return max;
}
void supprimer_client(int i)
{
	printf("Suppression du client à l'emplacement %d\n", i);
	FD_CLR(client[i].fd, &masterfds);
	close(client[i].fd);
	client[i].fd = 0;
}
void clore_les_sockets(void)
{
	int i = 0;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(client[i].fd > 0)
			close(client[i].fd);
	close(sockfd);
}
void renvoyer_message(int nclient)
{
	int i;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(i != nclient && client[i].fd != 0)
			sendto(client[i].fd, buf, TAILLE_BUFFER, 0,
					(struct sockaddr *) &client[i].adr,
					sizeof(client[i].adr));
}
void sortie_programme(void)
{
	// Pour ne pas que ça n'écrive quelque-chose sur la ligne de commande
	// Au cas où vous ne rentreriez pas ^D comme prévu
	read(0, buf, TAILLE_BUFFER);
	printf("\nVous avez fait ^D, vous quittez le programme\n");
	clore_les_sockets();
	exit(EXIT_SUCCESS);
}
void recevoir_utilisateur(int nclient)
{
	int rt;
	rt = recv(client[nclient].fd, buf, TAILLE_BUFFER, 0);

	if(rt < 0)				// Erreur sur la réception
		quitter("recv");	
	else if(rt == 0)		// On ne reçoit rien, il s'est déconnecté
		supprimer_client(nclient);
	else					// On a reçu, on renvoie aux autres clients
		renvoyer_message(nclient);
}
