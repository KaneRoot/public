/**
 * @file server-auctioneer.h
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
 * Ce fichier contient les descriptions des fonctions utiles pour le serveur.
 */
#ifndef __SERVER_AUCTIONEER_H__
#define __SERVER_AUCTIONEER_H__

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "../lib/definitions.h"
#include "../lib/structures.h"
#include "../lib/messages.h"

/** boucle principale du programme (utilisation de la fonction select).  */
void boucle_select(void);

/**
 * Quitte le programme en affichant un message d'erreur
 * 
 * @param erreur la chaîne de caractères décrivant l'erreur
 */
void quitter(char * erreur);
/**
 * Initialise le contexte, se charge d'appeler la fonction d'init des sockets etc.
 *
 * @param argc
 * @param argv
 */
void init_programme(int argc, char **argv);
/**
 * Se charge d'initialiser les sockets d'écoute tcp et udp
 *
 * @param port Le port sur lequel on écoute.
 */
void init_sockets(int port);
/** Gère la sortie du programme (sans erreur) */
void sortie_programme(void);
/** Clos les connexions et les sockets.  */
void clore_les_sockets(void);

/** Calcule le nombre d'enchérisseurs connectés.  */
int nombre_clients_bidder(void);
/** Trouve quel est le plus grand descripteur de fichiers.  */
int plus_grand_fd(void);
/** Affiche un récapitulatif des produits mis en vente.  */
void recap_produits(void);
/** Gère la réception d'un paquet sur socket udp du contexte serveur.  */
int reception_paquet(message_s * m, struct sockaddr_in * adresse, socklen_t * taille);
/**
 * Gère l'envoi d'un paquet (défini dans /lib/structures.h).
 *
 * @param idclient le numéro du client.
 * @param message le paquet à envoyer.
 */
void envoi_paquet(idclient_t id, message_s mes);
/** Le handler du signal d'alarme utilisé pour la gestion du temps.  */
void hand_alrm(int x);

/** Lorsque le programme se termine, on envoi un message à tous pour quitter */
void faire_quitter_les_clients(void);
/**
 * On envoi une description des marchandises mises aux enchères à un client.
 *
 * @param idclient
 */
void envoi_produits(idclient_t num_cli);
/**
 * On envoi une description du produit actuellement mis aux enchères à un client.
 *
 * @param idclient
 */
void envoi_produit_courant(idclient_t);
/** Nous gérons la déconnexion d'un client. */
void deconnexion_client(idclient_t i);
/** Fin des enchères : on envoit à tous ce qu'ils ont gagné.  */
void fin_encheres(void);
/**
 * Envoyer un message à tout le monde.
 * 
 * @param message le paquet à envoyer.
 */
void envoyer_a_tous(message_s mes);
/** dire à un client, un message (une simple chaîne de caractères). */
void dire(int nclient, char * adire);

/** Traitement d'un paquet venant d'un enchérisseur. */
void attendre_utilisateur(void);
/** Ànnoncer à tous les enchérisseurs qu'il y a une nouvelle offre.  */
void annoncer_nouveau_meilleur_encherisseur(void);
/** Gestion d'une réception d'une offre venant d'un enchérisseur. */
void reception_offre(idclient_t num_cli, objet_t objet, prix_t prix);
/** Envoyer un paquet à tous les enchérisseurs. */
void envoyer_paquet_aux_clients_bidder(message_s mes);

/** Suppression d'un vendeur. */
void supprimer_client_tcp(int);
/** Gestion de la connexion d'un vendeur. */
void attendre_vendeur(void);
/** Traitement d'un paquet venant d'un vendeur. */
void recevoir_vendeur(int nclient);
/** Gestion de la réception d'un nouveau produit à vendre. */
void reception_produit(message_s mes);

/** 
 * Vérifier que l'utilisateur est bien enregistré. 
 * @param mes le message reçu
 */
int est_autorise(message_s mes);
/**
 * Renvoi d'un message d'erreur de connexion à l'utilisateur non autorisé
 * @param mes : le message reçu mais non autorisé
 */
void renvoi_erreur_connexion(message_s mes);
/**
 * Recevoir un message sur le port udp.
 * @param mes : la structure message_s dans laquelle on écrit.
 */
void recevoir_message_udp(message_s * mes);

#endif
