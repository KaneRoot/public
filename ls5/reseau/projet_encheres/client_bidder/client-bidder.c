/**
 * @file client-bidder.c
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
 * Ce fichier contient les fonctions utiles pour la gestion de l'enchérisseur.
 */
#include "client-bidder.h"

context_bidder_s ctxt;

int main(int argc, char **argv)
{

	init_programme(argc, argv);

	boucle_select();

	// On ne devrait pas revenir ici
	deconnexion();
	clore_les_sockets();

    return EXIT_FAILURE;
}
void boucle_select(void)
{
	int i, rt;
	while(1)
	{
		memcpy(&ctxt.readfds, &ctxt.masterfds, sizeof(fd_set));
		bzero(ctxt.tampon, TAILLE_BUFFER); // On vide le tampon

		rt = select(FD_SETSIZE, &ctxt.readfds, NULL, NULL, NULL);
		if(rt < 0)
			quitter("select");

		for(i = 0 ; i < FD_SETSIZE ; i++)
		{
			if(FD_ISSET(i, &ctxt.readfds))
			{
				if(i == 0)	// lecture entrée standard + envoi
					envoyer_donnee();
				else		// lecture socket liée au serveur + écriture
					recevoir_donnee();
			}
		}

	}
}
void sortie_programme(void)
{
	deconnexion();
	clore_les_sockets();
	printf(m_sortie_programme);
	exit(EXIT_SUCCESS);
}
void init_programme(int argc, char *argv[])
{
	int port;
	char ip[TAILLE_BUFFER];

	ctxt.numero_client = CB_CLIENT_NON_CONNECTE;

	/** Tout est par défaut. */
	if(argc == 1)
	{
		printf(m_connexion_par_defaut);
		port = PORT;
		memcpy(ip, ADRESSE_PAR_DEFAUT, TAILLE_BUFFER);
	}
	else
	{
		memcpy(ip, argv[1], TAILLE_BUFFER);
		port = (argc == 3) ? atoi(argv[2]) : PORT;
	}

	if(NULL == strstr(ip, ":")) // S'il n'y a pas de ':' alors IPv4
	{
		if(inet_pton(AF_INET, ip, &ctxt.server.sin_addr) < 0)
		{
			quitter("inet_pton");
		}
		ctxt.server.sin_family		= AF_INET;
		ctxt.server.sin_port		= htons(port);
		ctxt.addrlen = sizeof(struct sockaddr_in);

		if((ctxt.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
			quitter("socket");
	}
	else
	{
		// get addr from command line and convert it
		if(inet_pton(AF_INET6, ip, &ctxt.server6.sin6_addr) < 0)
		{
			quitter("inet_pton");
		}
		else
		{
			ctxt.addrlen = sizeof(struct sockaddr_in6);
			ctxt.server6.sin6_family	= AF_INET6;
			ctxt.server6.sin6_port		= htons(port + 1);

			if((ctxt.sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) == -1) 
				quitter("socket");
		}
	}

	ctxt.produit_courant = 0;
	connexion();

	FD_ZERO(&ctxt.masterfds);
	FD_SET(0, &ctxt.masterfds);		// On écoute sur l'entrée standard
	FD_SET(ctxt.sockfd, &ctxt.masterfds);

	printf(m_debut_prog);
	printf(m_demande_action);
}
void connexion(void)
{
	char * passwd_chiffre;
	printf("Connexion… (voir readme pour les utilisateurs autorisés pour debug) \n");
	bzero(&ctxt.mes, sizeof(message_s));
	ctxt.mes.type = T_DEMANDE_CONNEXION;

	printf(m_demande_nom);
	fflush(stdout);
	if( read(0, ctxt.tampon, TAILLE_BUFFER) < 0)
		quitter("read");
	
	ctxt.tampon[strlen(ctxt.tampon) -1] = '\0';
	memcpy(ctxt.mes.ident.nom, ctxt.tampon, TAILLE_BUFFER);
	memcpy(ctxt.ident.nom, ctxt.tampon, TAILLE_BUFFER);

	passwd_chiffre = crypt(getpass(m_demande_pass), MDP_SALT);
	memcpy(ctxt.ident.passwd, passwd_chiffre, TAILLE_BUFFER);
	memcpy(ctxt.mes.ident.passwd, passwd_chiffre, TAILLE_BUFFER);

	envoyer_paquet(ctxt.mes);
	bzero(&ctxt.mes, sizeof(message_s));
	recevoir_paquet(&ctxt.mes);

	if(ctxt.mes.type == T_CONNEXION_REFUSEE)
	{
		quitter("Erreur : la connexion à été refusée.");
	}
	printf(m_ligne_vide);
	ctxt.numero_client = ctxt.mes.id;
	bzero(&ctxt.mes, sizeof(message_s));
}
void clore_les_sockets(void)
{
	// Qu'un socket à fermer.
	close(ctxt.sockfd);
}
void envoyer_donnee(void)
{
	int rt;

	rt = read(0, ctxt.tampon, TAILLE_BUFFER);
	if(rt < 0)
		quitter("read");
	else if(rt == 0)
		sortie_programme();

	switch(atoi(ctxt.tampon))
	{
		case CB_DEMANDE_PRODUITS :
			faire_demande_produits();
			break;
		case CB_FAIRE_OFFRE :
			if( -1 == faire_offre())
			{
				printf(m_mauvais_type);
			}
			break;
		case CB_DEMANDE_PRODUIT_COURANT :
			bzero(&ctxt.mes, sizeof(message_s));
			ctxt.mes.type = T_DEMANDE_PRODUIT_COURANT;
			envoyer_paquet(ctxt.mes);
			break;
		default :
			printf(m_mauvais_type);
	}

	// On vide le tampon
	fflush(stdin);
	printf(m_demande_action);
}
void recevoir_donnee(void)
{
	recevoir_paquet(&ctxt.mes);

	switch(ctxt.mes.type)
	{
		case T_ENVOI_INFOS_PRODUITS :
			printf(m_ligne_vide);
			while(ctxt.mes.type == T_ENVOI_INFOS_PRODUITS)
			{
				printf("%d. '%s' pour un prix actuel de \033[32m%d €\033[00m.\n", 
						ctxt.mes.objet, ctxt.mes.message, ctxt.mes.offre);
				recevoir_paquet(&ctxt.mes);
			}
			printf(m_ligne_vide);
			break;
		case T_SIMPLE_MESSAGE :
			printf(m_reception_message); fflush(stdout);
			printf("%s\n", ctxt.mes.message);
			break;
		case T_PRODUIT_SUIVANT :
			printf(m_produit_suivant);
			ctxt.produit_courant = ctxt.mes.objet;
		case T_REPONSE_PRODUIT_COURANT :
			printf("Produit courant : '%s' num '%d' à \033[32m%d €\033[00m.\n", 
				ctxt.mes.message, ctxt.produit_courant, ctxt.mes.offre);
			break;
		case T_FIN_ENCHERES :
			printf(m_fin_encheres);
			recevoir_paquet(&ctxt.mes);
			while(ctxt.mes.type != T_FIN_TRANSMISSION)
			{
				printf("J'ai remporté \033[36m'%s'\033[00m pour \033[32m%d €\033[00m TTC.\n", ctxt.mes.message, ctxt.mes.offre);
				recevoir_paquet(&ctxt.mes);
			}
			// Fin du scénario
			sortie_programme();
			break;
		case T_DECONNEXION :
			sortie_programme();
			break;
		default :
			printf(m_mauvais_type);
	}
	bzero(&ctxt.mes, sizeof(message_s));
}
void deconnexion(void)
{
	if(ctxt.numero_client == CB_CLIENT_NON_CONNECTE)
		return ;

	bzero(&ctxt.mes, sizeof(message_s));
	ctxt.mes.id = ctxt.numero_client;
	ctxt.mes.type = T_DECONNEXION;

	envoyer_paquet(ctxt.mes);
}
void quitter(char * erreur)
{
	deconnexion();
	perror(erreur);
	clore_les_sockets();
	exit(EXIT_FAILURE);
}
void faire_demande_produits(void)
{
	ctxt.mes.id = ctxt.numero_client;
	ctxt.mes.type = T_DEMANDE_INFOS_PRODUITS;
	envoyer_paquet(ctxt.mes);
}
// Si -1 : on ne veut pas faire d'offre
int faire_offre(void)
{
	int rt;

	printf(m_demande_prix);
	fflush(stdout);

	bzero(ctxt.tampon, TAILLE_BUFFER); // On vide le tampon
	rt = read(0, ctxt.tampon, TAILLE_BUFFER);
	if(rt < 0)
		perror("Erreur à la lecture de l'offre\n");
	else if (rt == 0) // Nous n'entrons rien, on ne souhaite plus faire l'offre ?
		return -1;

	ctxt.mes.objet = ctxt.produit_courant;
	ctxt.mes.offre = atoi(ctxt.tampon);
	ctxt.mes.id = ctxt.numero_client;
	ctxt.mes.type = T_ENVOI_OFFRE;
	envoyer_paquet(ctxt.mes);

	return 0;
}
void envoyer_paquet(message_s m)
{
	/**
	 * On réécrit les informations nous concernant pour nous identifier.
	 */
	m.id = ctxt.numero_client;
	memcpy(m.ident.nom, ctxt.ident.nom, TAILLE_BUFFER);
	memcpy(m.ident.passwd, ctxt.ident.passwd, TAILLE_BUFFER);
	if(ctxt.addrlen == sizeof(struct sockaddr_in6))
	{
		if(sendto(ctxt.sockfd, &m, sizeof(message_s), 0,
					(struct sockaddr *) &ctxt.server6, ctxt.addrlen) < 0)
			perror("Erreur à l'envoi d'un message");
	}
	else
	{
		if(sendto(ctxt.sockfd, &m, sizeof(message_s), 0,
					(struct sockaddr *) &ctxt.server, ctxt.addrlen) < 0)
			perror("Erreur à l'envoi d'un message");
	}
}
void recevoir_paquet(message_s * m)
{
	int rt ;
	rt = recvfrom(ctxt.sockfd, m, sizeof(message_s), 0, NULL, NULL);
	if(rt < 0)
		quitter("recv");
}
