// TEST : ./get karchnu.fr /accueil/index.html

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

#define TAILLE_REQUETE 1024
#define TAILLE_BUFFER 1024

int main(int argc, char **argv)
{
    int sockfd, rv, nlues;
	struct addrinfo hints, *servinfo, *p;
	char requete[TAILLE_REQUETE], buf[TAILLE_BUFFER];

	bzero(requete, TAILLE_REQUETE);
	
    if(argc != 3)
    {
        printf("USAGE: %s server file\n", argv[0]); // a légèrement changé
		printf("Exemple : %s karchnu.fr /accueil/index.php\n", argv[0]);
		return EXIT_FAILURE;
    }

	// On construit la requête
	snprintf(requete, TAILLE_REQUETE, "GET %s HTTP/1.1\nhost: %s\n\n", argv[2], argv[1]);
	printf("REQUETE : \n%s", requete);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;		// Peu importe que ce soit de l'IPv4 ou 6
	hints.ai_socktype = SOCK_STREAM;	// TCP

	// On récupère les informations sur le serveur (servinfo)
	if ((rv = getaddrinfo(argv[1], "http", &hints, &servinfo)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return EXIT_FAILURE;
	}

	// Boucle sur chaque résultat de getaddrinfo tant qu'on arrive pas à se connecter
	for(p = servinfo; p != NULL; p = p->ai_next) 
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
		{
			perror("socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
		{
			close(sockfd);
			perror("connect");
			continue;
		}

		if(sendto(sockfd, requete, TAILLE_REQUETE, 0,
					servinfo->ai_addr,
					servinfo->ai_addrlen) < 0)
		{
			perror("sendto");
			return EXIT_FAILURE;
		}


		// On écrit tout ce qu'on reçoit sur le terminal
		while( (nlues = recv(sockfd, buf, TAILLE_BUFFER, 0)) != 0)
			write(1, buf, nlues);

		break; // si on arrive là c'est qu'on est connecté
	}

	if (p == NULL) 
	{
		// On a terminé la boucle mais sans réussir à se connecter
		fprintf(stderr, "failed to connect\n");
		exit(2);
	}

	freeaddrinfo(servinfo); // à faire sur toutes les structures addrinfo

    return EXIT_SUCCESS;
}
