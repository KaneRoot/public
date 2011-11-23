
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <netdb.h>

int main (int argc, char *argv[])
{
	struct addrinfo *resultat;
	struct addrinfo hints;

	struct sockaddr_in  addr_recepteur; // structure d'adresse du recepteur
 	int size_addr_in = sizeof(struct sockaddr_in); // utile pour sendto	
	int aenvoyer = atoi(argv[3]);

    int s; // socket


	if (argc!=4)
	{
		fprintf(stderr, "Usage : %s @recepteur port_recepteur message\n",argv[0]);
		exit (1);
	}

	// création socket

	s = socket(AF_INET,SOCK_DGRAM,0);

  	// adresse recepteur	

	memset(&hints,0,sizeof hints);
	hints.ai_socktype = SOCK_DGRAM; // UDP
	hints.ai_family = AF_INET; // IPv4

	if (getaddrinfo(argv[1],NULL,&hints,&resultat))
	{
		fprintf(stderr, "erreur getddrinfo\n");
		exit (1);
	}
     
  	addr_recepteur.sin_family=resultat->ai_family;
  	addr_recepteur.sin_port=htons(atoi(argv[2]));
  	addr_recepteur.sin_addr=((struct sockaddr_in *)resultat->ai_addr)->sin_addr;

	
	if(sendto(s,&aenvoyer,sizeof(int),0,(struct sockaddr*)&addr_recepteur,size_addr_in) == -1)
 	{
		fprintf(stderr, "erreur sendto\n");
		exit(1);
	}

	// fermeture socket
	
	close(s);

	return 0;
}

