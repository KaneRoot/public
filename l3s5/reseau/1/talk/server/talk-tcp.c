#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LISTEN_BACKLOG 10
#define TAILLE_BUFFER 1024
#define NB_CLIENTS 5

typedef struct 
{
	int fd;						// socket
	struct sockaddr_in6 adr;	// info @
} client_s;

int sockfd;
char buf[TAILLE_BUFFER];
socklen_t addrlen;

void quitter(char * erreur);
void init_programme(int argc, char **argv);

int main(int argc, char **argv)
{
	init_programme(argc,argv);

	int nb_connexions = 0;
	client_s client[NB_CLIENTS];

	printf("Attente première connexion\n");
    if((client[0].fd = accept(sockfd, (struct sockaddr *)&client[0].adr, &addrlen)) == -1)
    {
        close(sockfd);
		quitter("accept");
    }
	while(0)
	{
		if(recv(client[0].fd, buf, TAILLE_BUFFER, 0) == -1)
		{
			close(sockfd);
			// CLOSE DES SOCKETS
			quitter("recv");
		}
	}

    close(sockfd);
	// CLOSE DES SOCKETS

    return 0;
}

void quitter(char * erreur)
{
	perror(erreur);
	exit(EXIT_FAILURE);
}

void init_programme(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("USAGE: %s port_num\n", argv[0]);
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
}
