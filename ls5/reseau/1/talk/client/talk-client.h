#ifndef __TALK_CLIENT_H__
#define __TALK_CLIENT_H__

void quitter(char * erreur);
void clore_les_sockets(void);
void init_programme(int argc, char *argv[]);
void sortie_programme(void);
void envoyer_donnee(void);
void recevoir_donnee(void);

#endif
