/**
 * @file client-bidder.h
 * @author Philippe Pittoli <kane point root chez gmail point com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Ce fichier contient les descriptions des fonctions liée à l'enchérisseur.
 *
 * @section MISCELLANEOUS
 *
 * Certaines fonctions ont un nom identique entre les deux types de client.
 * Cependant leur implémentation ne l'est pas.
 *
 * J'ai fait le choix de ne pas créer de fichier à part pour les regrouper.
 */
#ifndef __CLIENT_BIDDER_H__
#define __CLIENT_BIDDER_H__

/** Includes des bibliothèques. */
#include <unistd.h>
#include <crypt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../lib/definitions.h"
#include "../lib/structures.h"
#include "../lib/messages.h"

/**
 * Initialise le contexte, se charge d'appeler la fonction d'init des sockets etc.
 *
 * @param argc
 * @param argv
 */
void init_programme(int argc, char *argv[]);
/** boucle principale du programme (utilisation de la fonction select).  */
void boucle_select(void);
/** Clos la connexion.  */
void clore_les_sockets(void);
/** Gère la sortie du programme (sans erreur) */
void sortie_programme(void);
/**
 * Quitte le programme en affichant un message d'erreur
 * 
 * @param erreur la chaîne de caractères décrivant l'erreur
 */
void quitter(char * erreur);
/** Procédure appelée pour l'envoi d'un message. */
void envoyer_paquet(message_s m);
/** Procédure appelée pour la réception d'un message. */
void recevoir_paquet(message_s *m);
/** Procédure appelée lorsque le client écrit au clavier. */
void envoyer_donnee(void);
/** Procédure appelée lors de la réception d'une donnée sur le socket. */
void recevoir_donnee(void);


/** Procédure de connexion avec demande de mot de passe puis envoi du paquet. */
void connexion(void);
/** Déconnexion. */
void deconnexion(void);

/** Création d'un message de demande de la liste des produits puis envoi. */
void faire_demande_produits(void);
/** Procédure qui demande au client quel est le montant de l'offre puis l'envoi. */
int faire_offre(void);


#endif
