/**
 * @file client_seller.c
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
 * Ce fichier contient les fonctions utiles pour le vendeur.
 */

#include "client-seller.h"

context_seller_s ctxt;

int main(int argc, char **argv)
{
	init_programme(argc, argv);

	boucle_select();

	clore_les_sockets();

    return EXIT_FAILURE;
}
void boucle_select(void)
{
	int i, rt;

	FD_SET(0, &ctxt.masterfds);		// On écoute sur l'entrée standard
	FD_SET(ctxt.sockfd, &ctxt.masterfds); // On ajoute le socket lié au serveur
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
		printf(m_demande_action_seller);
	}

}
void sortie_programme(void)
{
	clore_les_sockets();
	printf(m_sortie_programme);
	exit(EXIT_SUCCESS);
}
void init_programme(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf(m_connexion_par_defaut);
	}
	int port;
	char ip[TAILLE_BUFFER];

	port = (argc == 3) ? atoi(argv[2]) : PORT;
	if(argc >= 2)
		memcpy(ip, argv[1], TAILLE_BUFFER);
	else
		memcpy(ip, ADRESSE_PAR_DEFAUT, TAILLE_BUFFER);


    // check the number of args on command line

    // socket factory
    if((ctxt.sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
	    exit(EXIT_FAILURE);
    }

    // init remote addr structure and other params
    ctxt.server.sin_family = AF_INET;
	ctxt.server.sin_port   = htons(port);
    ctxt.addrlen           = sizeof(struct sockaddr_in);

    // get addr from command line and convert it
    if(inet_pton(AF_INET, ip, &ctxt.server.sin_addr) < 0)
    {
        perror("inet_pton");
        close(ctxt.sockfd);
        exit(EXIT_FAILURE);
    }

    if(connect(ctxt.sockfd, (struct sockaddr *) &ctxt.server, ctxt.addrlen) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

	FD_ZERO(&ctxt.masterfds);
	printf(m_debut_prog);

	envoi_objets();

}
void quitter(char * erreur)
{
	perror(erreur);
	clore_les_sockets();
	exit(EXIT_FAILURE);
}
void clore_les_sockets(void)
{
	// Qu'un socket à fermer.
	close(ctxt.sockfd);
}
/** Nous envoyons nos objets. */
void envoi_objets(void)
{
	message_s mes;
	int nb_octets_lus;
	char tmp[TAILLE_BUFFER];
	printf(message_envoi_objets);

	/************************************************
	 * Tant que nous avons des fichiers à envoyer
	 * nous continuons à lire sur l'entrée standard
	 */


	while(1)
	{
		bzero(&mes, sizeof(message_s));

		printf(m_sender_nom_objet);
		fflush(stdout);

		bzero(tmp, TAILLE_BUFFER);
		if((nb_octets_lus = read(0, tmp, TAILLE_BUFFER -1 )) <= 0)
			break;
		tmp[TAILLE_BUFFER] = '\0';

		memcpy(mes.message, tmp, strlen(tmp) -1);
		mes.message[strlen(tmp)] = '\0';

		printf(m_sender_prix_depart);
		fflush(stdout);

		if((nb_octets_lus = read(0, tmp, TAILLE_BUFFER)) <= 0)
			break;
		mes.offre_debut = atoi(tmp);

		printf(m_sender_prix_minimal);
		fflush(stdout);

		bzero(tmp, TAILLE_BUFFER);
		if((nb_octets_lus = read(0, tmp, TAILLE_BUFFER)) <= 0)
			break;
		mes.offre_min = atoi(tmp);

		mes.type = T_SELLER_PRODUIT;

		envoyer_paquet(mes);
		printf(m_ligne_vide);
	}
	printf("\n"); printf(m_ligne_vide);
	printf(m_demande_action_seller);
}
void envoyer_donnee(void)
{
	int rt;
	message_s mes;
	bzero(&mes, sizeof(message_s));

	rt = read(0, ctxt.tampon, TAILLE_BUFFER);
	if(rt < 0)
		quitter("read");
	else if(rt == 0)
		sortie_programme();

	switch(atoi(ctxt.tampon))
	{
		case CS_DEMARRER_ENCHERES :
			mes.type = T_DEBUT_ENCHERES;
			envoyer_paquet(mes);
			break;
		case CS_CONSULTER_OFFRES :
			mes.type = T_DEMANDE_INFOS_PRODUITS;
			envoyer_paquet(mes);
			break;
		case CS_ENVOYER_OBJETS :
			envoi_objets();
			break;
		default :
			printf(m_mauvais_type);
	}

	// On vide le tampon
	fflush(stdin);
}
void recevoir_donnee(void)
{
	message_s mes;

	recevoir_paquet(&mes);

	switch(mes.type)
	{
		case T_SIMPLE_MESSAGE :
			printf(m_reception_message); fflush(stdout);
			printf("%s\n", mes.message);
			break;
		case T_ENVOI_INFOS_PRODUITS :
			printf(m_ligne_vide);
			while(mes.type != T_FIN_TRANSMISSION)
			{
				printf("%d. '%s' pour un prix actuel de %d \n", 
						mes.objet, mes.message, mes.offre);
				recevoir_paquet(&mes);
			}
			printf(m_ligne_vide);
			break;
		case T_IMPOSSIBLE_DEMARRER_ENCHERES :
			printf(m_encheres_non_demarrees);
			break;
		case T_FIN_ENCHERES :
			printf(m_fin_encheres);
			recevoir_paquet(&mes);
			while(mes.type != T_FIN_TRANSMISSION)
			{
				if(mes.type == T_OBJET_REMPORTE)
					printf("Produit '%s' remporté par '%s' pour %d € TTC.\n", 
						mes.message, mes.ident.nom, mes.offre);
				else
					printf("Produit '%s' non vendu.\n", mes.message);

				recevoir_paquet(&mes);
			}
			// Fin du scénario
			sortie_programme();
			break;
		default :
			printf(m_mauvais_type);
	}
}
void envoyer_paquet(message_s m)
{
	if(sendto(ctxt.sockfd, (void *) &m, 
				sizeof(message_s), 
				0, (struct sockaddr*) &ctxt.server, ctxt.addrlen) == -1)
		quitter("Impossible d'envoyer un paquet.");
}
void recevoir_paquet(message_s *m)
{
	int rt ;
	rt = recv(ctxt.sockfd, m, sizeof(message_s), 0);
	if(rt < 0)
		quitter("recv");
	else if(rt == 0) // Indique que le serveur a fermé sa socket
		sortie_programme();
}
