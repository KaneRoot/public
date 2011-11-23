
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main (int argc, char *argv[])
{
	struct sockaddr_in  addr_recepteur; // structure d'adresse du recepteur
 	struct sockaddr_in  addr_emetteur; // structure d'adresse de l'emetteur
	int msg; // message reçu
    int s; // socket
	socklen_t reception_length;

	if (argc!=2) { fprintf(stderr, "Usage : %s port_recepteur \n",argv[0]); exit (1); }	 
        
	// création socket
	s = socket(AF_INET,SOCK_DGRAM,0);
	// addresse recepteur	
  	addr_recepteur.sin_family=AF_INET; // IPv4
 	addr_recepteur.sin_port=htons(atoi(argv[1])); // numéro de port (converti au format network)
  	addr_recepteur.sin_addr.s_addr=INADDR_ANY;
	// association de la socket et du recepteur
	if(bind(s,(struct sockaddr*)&addr_recepteur,sizeof(struct sockaddr_in)))	
	{ 
		fprintf(stderr, "erreur bind\n"); 
		exit(1); 
	}
	// reception de la chaine
	if(recvfrom(s,&msg, sizeof(int),0,(struct sockaddr*)&addr_emetteur,&reception_length) == -1)
	{
		fprintf(stderr, "erreur recvfrom\n");
		exit(1);
	}	
	
	// affichage message reçu

	printf("message reçu: %d\n",msg);

	// fermeture socket
	
	close(s);

	return 0;
}

