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

int main(int argc, char **argv)
{
    int sockfd, rv;
	struct addrinfo hints, *servinfo, *p;
	char requete[TAILLE_REQUETE];

	bzero(requete, TAILLE_REQUETE);
	
    if(argc != 3)
    {
        printf("USAGE: %s @server file\n", argv[0]); // a légèrement changé
        exit(-1);
    }

	// On construit la requête
	snprintf(requete, TAILLE_REQUETE, "GET %s HTTP/1.1\nhost: %s\n\n", argv[2], argv[1]);
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // Peu importe que ce soit de l'IPv4 ou 6
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], "http", &hints, &servinfo)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results and connect to the first we can
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

		break; // si on arrive là c'est qu'on est connecté
	}

	if (p == NULL) 
	{
		// looped off the end of the list with no connection
		fprintf(stderr, "failed to connect\n");
		exit(2);
	}

	freeaddrinfo(servinfo); // a faire sur toutes les structures addrinfo

    return EXIT_SUCCESS;
}
