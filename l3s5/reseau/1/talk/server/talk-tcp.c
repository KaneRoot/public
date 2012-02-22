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
int nb_connexions = 0;
client_s client[NB_CLIENTS];
fd_set readfds, masterfds;

void quitter(char * erreur);
void init_programme(int argc, char **argv);
void attendre_utilisateur(void);
int plus_grand_fd(void);
void clore_les_sockets(void);
void supprimer_client(int);

int main(int argc, char **argv)
{
	int i, rt; // rt = return value

	init_programme(argc,argv);

	FD_SET(sockfd, &masterfds);

	while(1)
	{
		memcpy(&readfds, &masterfds, sizeof(fd_set));
		rt = select(plus_grand_fd() + 1, &readfds, NULL, NULL, NULL);
		for(i = 0 ; i <= plus_grand_fd() ; i++)
		{
			if(FD_ISSET(i, &readfds))
			{
				if(i == sockfd) // connexion entrante
					attendre_utilisateur();
				else
				{
					if((rt = recv(client[i].fd, buf, TAILLE_BUFFER, 0) == -1))
						quitter("recv"); // Erreur sur la réception
					if(rt == 0)
						supprimer_client(i);
				}
			}
			else
			{
			}
		}
	}

	clore_les_sockets();
    return 0;
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
	FD_ZERO(&masterfds);
}
void attendre_utilisateur(void)
{
	int i;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(client[i].fd <= 0)
			break;
	printf("Mise en attente de connexion à l'emplacement %d\n", i);
    if((client[i].fd = accept(sockfd, (struct sockaddr *) &client[i].adr, &addrlen)) == -1)
		quitter("accept");

	FD_SET(client[i].fd, &masterfds);
	printf("Connexion emplacement %d\n", i);
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
