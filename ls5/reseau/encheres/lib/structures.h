/**
 * @file structures.h
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
 * Ce fichier contient les structures utilisées dans les 3 programmes.
 */

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef struct {
	char nom[TAILLE_BUFFER];			/* nom du client. */
	char passwd[TAILLE_BUFFER];			/* mot de passe chiffré. */
} identification_s;

/* Si type = 1 : acheteur, si type = 0 : vendeur */
typedef struct {
	int fd;								/* socket */
	struct sockaddr_in adr;				/* info @ */
	socklen_t len;						/* taille @ */
	int type;							/* 1 si acheteur, 0 si vendeur. */
	identification_s ident;				/* L'identité du client. */
} client_s;

typedef struct {
	char nom[TAILLE_BUFFER];
	prix_t prix_min;
	prix_t prix_actuel;
	idclient_t client_sb;				/* L'id du client qui a le standing bid. */
	idclient_t vendeur;
} objet_s;

typedef struct {
	objet_t objet_actuel;
	int debut_encheres;					/* Marque le début des enchères. */
	int secondes_restantes;				/* Attente entre produits */
	int tcp_sock;						/* réception TCP */
	int udp_sock;						/* réception UDP */
	socklen_t addrlen;					/* La taille d'une adresse, ici 4 octets */
	struct sockaddr_in addrtmp;			/* Structure d'adresse temporaire. */
	fd_set readfds;						/* Les descripteurs où il y a de l'activité. */
	fd_set masterfds;					/* Les descripteurs que l'on surveille. */
	int nb_clients_co;					/* nombre de clients connectés */
	int nb_produits;					/* le nombre de produits en vente */
	objet_s les_produits[NB_PRODUITS];	/* Les objets à vendre */
	client_s client[NB_CLIENTS];		/* Nos clients */
	char tampon[TAILLE_BUFFER];			/* Chaîne de caractères utilisée comme buffer. */
} context_s;

/** Structure d'un message. */
typedef struct lemessage
{
	char message[TAILLE_BUFFER];		/* Suite de caractères. */
	identification_s ident;				/* L'identité du client. */
	idclient_t id;						/* Le numéro de client. */
	paquet_t type;						/* Le type du paquet (voir definitions.h). */
	// Suivi de quelques entiers qui nous serviront
	objet_t objet;						/* Numéro de l'article. */
	prix_t offre;						/* L'offre proposée. */
	prix_t offre_min;					/* L'offre minimale acceptée. */
	prix_t offre_debut;					/* L'offre de départ. */
} message_s;

typedef struct {
	identification_s ident;				/* L'identité du client. */
	fd_set masterfds;					/* Les descripteurs que l'on surveille. */
	fd_set readfds;						/* Les descripteurs où il y a de l'activité. */
	int sockfd;							/* Socket de communication avec le serveur. */
	struct sockaddr_in server;			/* L'adresse du serveur. */
	socklen_t addrlen;					/* La taille de l'adresse du serveur. */
	message_s mes;						/* Le message courant (reçu ou envoyé). */
	objet_t produit_courant;			/* Identifiant de l'article courant. */
	idclient_t numero_client ;			/* Le numéro du client. */
	char tampon[TAILLE_BUFFER];			/* Chaîne de caractères utilisée comme buffer. */
} context_bidder_s ;

typedef struct {
	fd_set masterfds;					/* Les descripteurs que l'on surveille. */
	fd_set readfds;						/* Les descripteurs où il y a de l'activité. */
	int sockfd;							/* Socket de communication avec le serveur. */
	struct sockaddr_in server;			/* L'adresse du serveur. */
	socklen_t addrlen;					/* La taille de l'adresse du serveur. */
	char tampon[TAILLE_BUFFER];			/* Chaîne de caractères utilisée comme buffer. */
} context_seller_s ;

#endif
