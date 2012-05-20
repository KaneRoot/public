/**
 * @file definitions.h
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
 * Ce fichier contient les différentes options par défaut
 * ainsi que la définition des types de message.
 */
#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/** Définitions de types de variables */
typedef int idclient_t;
typedef int paquet_t;
typedef int objet_t;
typedef int prix_t;

#define TAILLE_BUFFER 150

#define LISTEN_BACKLOG						10
#define NB_CLIENTS							10
#define NB_PRODUITS							10
#define ENCHERES_NON_DEBUTEES				0
#define ENCHERES_DEBUTEES					1
#define PRODUIT_NON_ACHETE					-1
#define TEMPS_ATTENTE						20
#define PORT								9000
#define ADRESSE_PAR_DEFAUT					"127.0.0.1"
#define FICHIER_UTILISATEURS				"../lib/utilisateurs_enregistres"
#define MDP_SALT							"$1$........"

/** Les différents types de message. */
#define T_DEMANDE_CONNEXION					1
#define T_VALIDATION_CONNEXION				2
#define T_DECONNEXION						3
#define T_CONNEXION_REFUSEE					4
#define T_ENVOI_INFOS_PRODUITS				5
#define T_ENVOI_OFFRE						6
#define T_DEBUT_ENCHERES					7
#define T_DEMANDE_INFOS_PRODUITS			8
#define T_FIN_TRANSMISSION					9
#define T_SIMPLE_MESSAGE					10
#define T_DEMANDE_PRODUIT_COURANT			11
#define T_REPONSE_PRODUIT_COURANT			12
#define T_RECAP_FIN_ENCHERES				14
#define T_SELLER_PRODUIT					15
#define T_IMPOSSIBLE_DEMARRER_ENCHERES		16
#define T_PRODUIT_SUIVANT					17
#define T_FIN_ENCHERES						18
#define T_OBJET_REMPORTE					19
#define T_OBJET_NON_REMPORTE				20

/** Définitions liées à un client. */
#define CB_CLIENT_NON_CONNECTE				-1
#define CB_DEMANDE_PRODUITS					1
#define CB_FAIRE_OFFRE						2
#define CB_DEMANDE_PRODUIT_COURANT			3

#define CS_DEMARRER_ENCHERES				1
#define CS_CONSULTER_OFFRES					2
#define CS_ENVOYER_OBJETS					3

#endif
