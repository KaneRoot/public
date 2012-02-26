#ifndef __TALK_SERVER_H__
#define __TALK_SERVER_H__

typedef struct 
{
	int fd;						// socket
	struct sockaddr_in6 adr;	// info @
} client_s;


void sortie_programme(void);
void quitter(char * erreur);
void init_programme(int argc, char **argv);
void attendre_utilisateur(void);
int plus_grand_fd(void);
void clore_les_sockets(void);
void supprimer_client(int);
void renvoyer_message(int nclient);
void recevoir_utilisateur(int nclient);

#endif
