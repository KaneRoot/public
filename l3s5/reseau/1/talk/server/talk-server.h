#ifndef __TALK_SERVER_H__
#define __TALK_SERVER_H__

typedef struct 
{
	int fd;						// socket
	struct sockaddr_in6 adr;	// info @
} client_s;


void quitter(char * erreur);
void init_programme(int argc, char **argv);
void attendre_utilisateur(void);
int plus_grand_fd(void);
void clore_les_sockets(void);
void supprimer_client(int);

#endif
