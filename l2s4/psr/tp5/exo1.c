#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

main(int argc, char *argv[])
{
	struct addrinfo hints; // 
	struct addrinfo *resultat;

	char stradr[INET_ADDRSTRLEN];

	if(argc!=2)
	{
		fprintf(stderr,"usage: %s <host>\n", argv[0]);
		exit(1);
	}

	memset(&hints,0,sizeof hints); /* remplit la structure de 0 */
	hints.ai_socktype = SOCK_DGRAM; /* UDP */
	hints.ai_family =  AF_INET; /* IPv4 */

	if(getaddrinfo(argv[1],NULL,&hints,&resultat))
	{
		fprintf(stderr,"erreur	getaddrinfo\n");
		exit(1);
	}

	inet_ntop(AF_INET,&((struct sockaddr_in *)resultat->ai_addr)->sin_addr, stradr,  INET_ADDRSTRLEN);

	printf("%s\n",stradr);

	freeaddrinfo(resultat);    

	exit(0);
}

