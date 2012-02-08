#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct addrinfo *resultat;
struct addrinfo hints;
struct sockaddr_in  addr_recepteur; // structure d'adresse du recepteur
struct sockaddr_in  addr_emetteur; // structure d'adresse de l'emetteur
int msg; // message reçu
int s; // socket
int numero_port_reception, numero_port_envoi;
char * adresse_recepteur;
void emettre(int valeur_a_transmettre)
{
  	addr_recepteur.sin_family=resultat->ai_family;
  	addr_recepteur.sin_port=htons(atoi(port));
  	addr_recepteur.sin_addr=((struct sockaddr_in *)resultat->ai_addr)->sin_addr;
	if(sendto(s,&valeur_a_transmettre,sizeof(int),0,(struct sockaddr*)&addr_recepteur,sizeof(struct sockaddr_in)) == -1)
 	{
		fprintf(stderr, "erreur sendto\n");
		exit(1);
	}
	return 0;
}
void truc(char * numero_port_reception)
{
	// création socket
	s = socket(AF_INET,SOCK_DGRAM,0);
	memset(&hints,0,sizeof hints);
	hints.ai_socktype = SOCK_DGRAM; // UDP
	hints.ai_family = AF_INET; // IPv4
	if(getaddrinfo(adresse_recepteur,NULL,&hints,&resultat))
	{
		fprintf(stderr, "erreur getddrinfo\n");
		exit (1);
	}

	close(s);
}
void recevoir()
{
	socklen_t reception_length;

	// addresse recepteur	
  	addr_recepteur.sin_family=AF_INET; // IPv4
 	addr_recepteur.sin_port=htons(atoi(argv[1])); // numéro de port (converti au format network)
  	addr_recepteur.sin_addr.s_addr=INADDR_ANY;
	if (argc!=2) { fprintf(stderr, "Usage : %s port_recepteur \n",argv[0]); exit (1); }	 
        
	// association de la socket et du recepteur
	if(bind(s,(struct sockaddr*)&addr_recepteur,sizeof(struct sockaddr_in)))	
	{ 
		fprintf(stderr, "erreur bind\n"); 
		exit(1); 
	}
	if(recvfrom(s,&msg, sizeof(int),0,(struct sockaddr*)&addr_emetteur,&reception_length) == -1)
	{
		fprintf(stderr, "erreur recvfrom\n");
		exit(1);
	}	
	printf("message reçu: %d\n",msg);

	return 0;
}
int main(int argc, char * argv[])
{
	if(strcmp(argv[0], "rec") == 0)
	{
	}
	else
	{
		numero_port_reception = argv[1];
		adresse_recepteur = argv[2];
		numero_port_envoi = atoi(argv[3]);
	}
	return EXIT_SUCCESS;
}

