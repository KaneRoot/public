#ifndef __TALK_CLIENT_H__
#define __TALK_CLIENT_H__

void quitter(char * erreur);
int plus_grand_fd(void);
void clore_les_sockets(void);
void init_programme(int argc, char *argv[]);
void sortie_programme(void);
void envoyer_donnee(void);

#endif
