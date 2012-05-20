/**
 * @file server-auctioneer.c
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
 * Ce fichier contient les fonctions utiles pour le serveur.
 */
#include "server-auctioneer.h"

context_s ctxt;						/* Le contexte. */

int main(int argc, char **argv)
{
	init_programme(argc,argv);

	boucle_select();

	// On ne devait pas sortir de la boucle
	clore_les_sockets();
    return EXIT_FAILURE;
}
void boucle_select(void)
{
	int i, rt, plusgrandfd; // rt = return value

	// On ne quitte pas cette boucle sauf pour terminer le programme
	while(1) 
	{
		memcpy(&ctxt.readfds, &ctxt.masterfds, sizeof(fd_set));
		bzero(ctxt.tampon, TAILLE_BUFFER); // On vide le tampon

		plusgrandfd = plus_grand_fd();
		rt = select(plusgrandfd + 1, &ctxt.readfds, NULL, NULL, NULL);

		/** Si select a été interrompu par le signal. */
		if(rt < 0)
			continue;

		for(i = 0 ; i <= plusgrandfd ; i++)
		{
			if(FD_ISSET(i, &ctxt.readfds))
			{
				//printf("Il y a de l'activité sur %d\n", i);
				if(i == ctxt.tcp_sock)		// connexion entrante
					attendre_vendeur();
				else if (i == ctxt.udp_sock)
					attendre_utilisateur();
				else if(i == 0)
					sortie_programme();
				else if(i >= 5 && i < NB_CLIENTS + 5)	// utilisateurs
					recevoir_vendeur(i - 5);
			}
		}
	}

}
void quitter(char * erreur)
{
	faire_quitter_les_clients();
	clore_les_sockets();
	perror(erreur);
	exit(EXIT_FAILURE);
}
void init_programme(int argc, char **argv)
{
	int port;

	port = (argc < 2) ? PORT : atoi(argv[1]);

	ctxt.debut_encheres = ENCHERES_NON_DEBUTEES;
	ctxt.secondes_restantes = TEMPS_ATTENTE;
	init_sockets(port);
	//attendre_vendeur();

	/** ALARM = signal que l'on utilise pour gérer le temps. */
	struct sigaction action;
	action.sa_handler = hand_alrm;
	sigaction(SIGALRM, &action, NULL);

	// Au cas où on veuille quitter (^D)
	FD_SET(0, &ctxt.masterfds);
	FD_SET(ctxt.tcp_sock, &ctxt.masterfds);
	FD_SET(ctxt.udp_sock, &ctxt.masterfds);
}
void init_sockets(int port)
{
	int yes = 1;
    struct sockaddr_in my_addr;

    if((ctxt.tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		quitter("socket TCP");

    if((ctxt.udp_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		quitter("socket UDP");

    my_addr.sin_family		= AF_INET;
    my_addr.sin_port		= htons(port);
	my_addr.sin_addr.s_addr	= INADDR_ANY;
    ctxt.addrlen                 = sizeof(struct sockaddr_in);
    memset(ctxt.tampon,'\0',TAILLE_BUFFER);

	/** 
	 * Pratique pour ne pas avoir d'erreur de bind
	 * On réutilise l'adresse de la socket même si elle n'a as été supprimée par le kernel
	 */
	if( 0 > setsockopt(ctxt.tcp_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
		perror("setsockopt");

    if(bind(ctxt.tcp_sock, (struct sockaddr *)&my_addr, ctxt.addrlen) == -1)
		quitter("bind tcp");

    if(bind(ctxt.udp_sock, (struct sockaddr *)&my_addr, ctxt.addrlen) == -1)
		quitter("bind udp");

    if(listen(ctxt.tcp_sock, LISTEN_BACKLOG) == -1)
		quitter("listen");

	FD_ZERO(&ctxt.masterfds);

	printf(m_debut_prog);

}
void attendre_utilisateur(void)
{
	message_s mes;
	bzero(&mes, sizeof(message_s));

	recevoir_message_udp(&mes);

	//printf("Réception de '%s' :: pass '%s'\n", mes.ident.nom, mes.ident.passwd);
	if(est_autorise(mes) == -1)
	{
		renvoi_erreur_connexion(mes);
		return;
	}
	switch(mes.type)
	{
		case T_DEMANDE_CONNEXION :
			if(ctxt.debut_encheres == ENCHERES_NON_DEBUTEES && 
					ctxt.nb_clients_co != NB_CLIENTS)
			{
				int i; // Numéro du client
				for(i = 0 ; i < NB_CLIENTS ; i++)
					if(ctxt.client[i].type != 1 && ctxt.client[i].fd == 0)
						break;

				mes.type = T_VALIDATION_CONNEXION;

				/** On initialise les variables liées à ce nouvel utilisateur. */
				ctxt.client[i].adr = ctxt.addrtmp;
				ctxt.client[i].len = ctxt.addrlen;
				ctxt.client[i].type = 1;	
				ctxt.client[i].fd = 1;
				memcpy(ctxt.client[i].ident.nom, mes.ident.nom, TAILLE_BUFFER);

				// On lui envoie son numéro de client
				envoi_paquet(i, mes);
				printf("Connexion du client '%s' à l'emplacement %d.\n", ctxt.client[i].ident.nom, i);
				ctxt.nb_clients_co++;
			}
			else
			{
				renvoi_erreur_connexion(mes);
			}

			break;
		case T_DECONNEXION :
			deconnexion_client(mes.id);
			ctxt.nb_clients_co--;
			break;
		case T_DEMANDE_PRODUIT_COURANT :
			envoi_produit_courant(mes.id);
			break;
		case T_DEMANDE_INFOS_PRODUITS :
			envoi_produits(mes.id);
			break;
		case T_ENVOI_OFFRE :
			reception_offre(mes.id, mes.objet, mes.offre);
			break;
		default :
			fprintf(stderr, "Message reçu non compris\n");
	}
}
void attendre_vendeur(void) 
{
	int i; // Numéro de vendeur

	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(ctxt.client[i].fd <= 0)
			break;
    if((ctxt.client[i].fd = accept(ctxt.tcp_sock, 
					(struct sockaddr *) &ctxt.client[i].adr, 
					&ctxt.addrlen)) == -1)
		quitter("accept");

	FD_SET(ctxt.client[i].fd, &ctxt.masterfds);
	//printf("Connexion à l'emplacement %d\n", i);
	ctxt.nb_clients_co++;
	//printf("Nombre de clients connectés : %d\n", ctxt.nb_clients_co);
}
int plus_grand_fd(void)
{
	int i, max = -1;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(ctxt.client[i].fd > max)
			max = ctxt.client[i].fd;
	max = (max > ctxt.tcp_sock) ? max : ctxt.tcp_sock;
	return max;
}
void supprimer_client_tcp(int i)
{
	printf("Suppression du client à l'emplacement %d\n", i);
	FD_CLR(ctxt.client[i].fd, &ctxt.masterfds);
	close(ctxt.client[i].fd);
	ctxt.client[i].fd = 0;
	ctxt.nb_clients_co--;
	printf("Nombre de clients connectés : %d\n", ctxt.nb_clients_co);
}
void clore_les_sockets(void)
{
	int i = 0;
	close(ctxt.tcp_sock);
	for(i = 0 ; i < ctxt.nb_clients_co ; i++)
		if(ctxt.client[i].fd >= 0 && ctxt.client[i].type != 1)
			close(ctxt.client[i].fd);
	close(ctxt.udp_sock);
}
void sortie_programme(void)
{
	// Pour ne pas que ça n'écrive quelque-chose sur la ligne de commande
	// Au cas où vous ne rentreriez pas ^D comme prévu
	read(0, ctxt.tampon, TAILLE_BUFFER);
	fflush(stdin);
	printf(m_sortie_programme);
	faire_quitter_les_clients();
	clore_les_sockets();
	exit(EXIT_SUCCESS);
}
void recevoir_vendeur(int nclient)
{
	int rt;
	message_s mes;
	bzero(&mes, sizeof(message_s));

	rt = recv(ctxt.client[nclient].fd, &mes, sizeof(message_s), 0);
	mes.id = nclient;

	if(rt < 0)				// Erreur sur la réception
		quitter("recv");	
	else if(rt == 0)		// On ne reçoit rien, il s'est déconnecté
		supprimer_client_tcp(nclient);
	else
	{
		switch(mes.type)
		{
			case T_DEBUT_ENCHERES :
				if(nombre_clients_bidder() >= 2 && ctxt.debut_encheres != ENCHERES_DEBUTEES)
				{
					printf(m_debut_encheres);
					mes.type = T_SIMPLE_MESSAGE;
					memcpy(mes.message, m_debut_encheres, TAILLE_BUFFER);
					envoyer_a_tous(mes);
					ctxt.debut_encheres = ENCHERES_DEBUTEES;
					alarm(1); // Déclenche la décrémentation
				}
				else
				{
					mes.type = T_IMPOSSIBLE_DEMARRER_ENCHERES;
					envoi_paquet(nclient, mes);
				}
				break;
			case T_SELLER_PRODUIT :
				reception_produit(mes);
				break;
			case T_DEMANDE_INFOS_PRODUITS :
				envoi_produits(nclient);
				break;
			default :
				printf(m_mauvais_type);
		}
	}
}
int nombre_clients_bidder(void)
{
	int i = 0;
	int tmp = ctxt.nb_clients_co;
	while(--tmp >= 0)
		if(ctxt.client[tmp].type == 1)
			i++;

	return i;
}
void recap_produits(void)
{
	int nombre = ctxt.nb_produits;
	while(--nombre >= 0)
	{
		printf("\nProduit Numéro %d : %s\nprix minimal : %d\n",
				nombre, ctxt.les_produits[nombre].nom, ctxt.les_produits[nombre].prix_min);
	}
}
void deconnexion_client(idclient_t i)
{
	printf("Déconnexion du client %d : '%s' \n", i, ctxt.client[i].ident.nom);
	if(ctxt.client[i].type != 1)
		close(ctxt.client[i].fd);
	ctxt.client[i].fd = 0;
	ctxt.client[i].type = 0;
	bzero( (void *) &ctxt.client[i].adr, ctxt.client[i].len);
	ctxt.client[i].len = 0;
}
void faire_quitter_les_clients(void)
{
	int i;
	for(i = 0 ; i < ctxt.nb_clients_co ; i++)
	{
		if(ctxt.client[i].type == 1)
			dire(i, "");
	}
}
/** Réception d'un message en UDP. */
int reception_paquet(message_s * m, struct sockaddr_in * adresse, socklen_t * taille)
{
	return recvfrom(ctxt.udp_sock, (void *) m, sizeof(message_s), 0,
				(struct sockaddr *) adresse, taille) ;
}
/** Envoyer les produits à un client qui les réclame. */
void envoi_produits(idclient_t num_cli)
{
	message_s produit;
	int nombre = ctxt.nb_produits;
	while(--nombre >= 0)
	{
		memcpy(produit.message, ctxt.les_produits[nombre].nom, TAILLE_BUFFER);
		produit.objet = nombre; // Numéro de produit
		produit.offre = ctxt.les_produits[nombre].prix_actuel;
		produit.type = T_ENVOI_INFOS_PRODUITS;

		envoi_paquet(num_cli, produit);

	}
	produit.type = T_FIN_TRANSMISSION;
	envoi_paquet(num_cli, produit);
}
void reception_offre(idclient_t num_cli, objet_t objet, prix_t prix)
{
	if(ctxt.debut_encheres == ENCHERES_NON_DEBUTEES)
		dire(num_cli, m_err_reception_offre_encheres_non_debutees);
	else if(objet >= ctxt.nb_produits)
		dire(num_cli, m_err_reception_offre_num_produit);
	else if (objet != ctxt.objet_actuel)
		dire(num_cli, m_err_reception_offre_num_objet);
	else if(ctxt.les_produits[objet].prix_actuel < prix)
	{
		printf("Nous avons reçu une offre de %d : '%s' pour %d € TTC\n", 
				num_cli, ctxt.les_produits[objet].nom, prix);
		ctxt.secondes_restantes = TEMPS_ATTENTE;
		ctxt.les_produits[ctxt.objet_actuel].prix_actuel = prix;
		ctxt.les_produits[ctxt.objet_actuel].client_sb = num_cli;
		annoncer_nouveau_meilleur_encherisseur();
	}
}
/** Nous annonçons à tous qu'il y a un nouveau meilleur enchérisseur. */
void annoncer_nouveau_meilleur_encherisseur(void)
{
	int i = 0;
	char message[TAILLE_BUFFER];

	snprintf(message, TAILLE_BUFFER - 1, 
			"\033[36m\tNouvel enchérisseur\033[00m : '%s' sur l'objet '%s', prix %d €.\n",
		   ctxt.client[ctxt.les_produits[ctxt.objet_actuel].client_sb].ident.nom,
		   ctxt.les_produits[ctxt.objet_actuel].nom,
		   ctxt.les_produits[ctxt.objet_actuel].prix_actuel);
	while(i < NB_CLIENTS)
	{
		// On envoie le nouveau meilleur enchérisseur qu'aux clients bidder
		if(ctxt.client[i].type == 1 && 
				ctxt.client[i].len != 0 &&
				i != ctxt.les_produits[ctxt.objet_actuel].client_sb)
		{
			dire(i, message);
		}
		i++;
	}
}
void envoi_produit_courant(idclient_t id)
{
	message_s mes;
	bzero(&mes, sizeof(message_s));
	mes.type = T_REPONSE_PRODUIT_COURANT;
	memcpy(mes.message, ctxt.les_produits[ctxt.objet_actuel].nom, TAILLE_BUFFER);
	mes.objet = ctxt.objet_actuel;
	mes.offre = ctxt.les_produits[ctxt.objet_actuel].prix_actuel;

	envoi_paquet(id, mes);
}
void envoi_paquet(idclient_t id, message_s mes)
{
	mes.id = id; // Au cas où on souhaite faire des tests sur le numéro de client
	/** Si c'est un client BIDDER. */
	if(ctxt.client[id].type == 1)
	{
		if( 0 > sendto( ctxt.udp_sock, 
					&mes, sizeof(message_s), 
					0,
					(struct sockaddr *) &ctxt.client[id].adr, 
					ctxt.client[id].len))
			quitter("sendto");
	}
	else
	{
		if( 0 > sendto( ctxt.client[id].fd, 
					&mes, sizeof(message_s), 
					0,
					(struct sockaddr *) &ctxt.client[id].adr,
					sizeof(ctxt.client[id].adr)))
			quitter("sendto");
	}
}
/* Envoyer un simple message. */
void dire(int nclient, char * adire)
{
	message_s mes;
	memset(&mes, 0, sizeof(message_s));
	memcpy(mes.message, adire, TAILLE_BUFFER);
	mes.message[strlen(adire)] = '\0';

	mes.type = T_SIMPLE_MESSAGE;
	if(strlen(adire) == 0)
		mes.type = T_DECONNEXION;

	envoi_paquet(nclient, mes);
}
void reception_produit(message_s mes)
{
	int i = ctxt.nb_produits;
	ctxt.les_produits[i].vendeur = mes.id;
	ctxt.les_produits[i].prix_min = mes.offre_min;
	ctxt.les_produits[i].prix_actuel = mes.offre_debut;
	memcpy(ctxt.les_produits[i].nom, mes.message, TAILLE_BUFFER);
	ctxt.les_produits[i].client_sb = PRODUIT_NON_ACHETE;

	printf("Le vendeur %d ajoute un produit : '%s', début à %d € et prix min %d €.\n",
			mes.id, ctxt.les_produits[i].nom, 
			ctxt.les_produits[i].prix_actuel, ctxt.les_produits[i].prix_min);

	ctxt.nb_produits++;
}
void hand_alrm(int x)
{
	x = x; // Valeur quelconque != 0
	if(ctxt.debut_encheres == ENCHERES_DEBUTEES)
	{
		ctxt.secondes_restantes--;
		printf("Il reste %d secondes.\n", ctxt.secondes_restantes);
		if(ctxt.secondes_restantes == 0)
		{
			message_s mes;
			bzero(&mes, sizeof(message_s));
			mes.type = T_PRODUIT_SUIVANT;

			// On redémarre le compteur
			ctxt.secondes_restantes = TEMPS_ATTENTE;
			ctxt.objet_actuel++;
			if(ctxt.objet_actuel == ctxt.nb_produits)
			{
				fin_encheres();
				return ;
			}
			memcpy(mes.message, ctxt.les_produits[ctxt.objet_actuel].nom, TAILLE_BUFFER);
			mes.offre = ctxt.les_produits[ctxt.objet_actuel].prix_actuel ;
			mes.objet = ctxt.objet_actuel;
			envoyer_paquet_aux_clients_bidder(mes);

			ctxt.debut_encheres = ENCHERES_NON_DEBUTEES;
			// On doit arrêter de décrémenter le timer
			return;
		}
	}
	else // Si les enchères n'ont pas débutées : pas de décrémentation de compteur.
	{
		return;
	}
	alarm(1);
}
void fin_encheres(void)
{
	int i;

	printf(m_fin_encheres);
	message_s mes;
	bzero(&mes, sizeof(message_s));
	mes.type = T_FIN_ENCHERES;
	/**
	 * à partir de là ils se mettent tous en attente des objets remportés
	 **/
	envoyer_a_tous(mes);
	/** 
	 * Pour tous les produits, 
	 * on envoit qui a remporté l'enchère à l'aquéreur et au vendeur.
	 */


	for(i = 0 ; i < ctxt.nb_produits ; i++)
	{
		mes.type = T_OBJET_REMPORTE;

		/** On place le nom du produit dans le message. */
		memcpy(mes.message, ctxt.les_produits[i].nom, TAILLE_BUFFER);
		mes.objet = i;

		if(ctxt.les_produits[i].client_sb != PRODUIT_NON_ACHETE)
		{
			mes.offre = ctxt.les_produits[i].prix_actuel;
			memcpy(	mes.ident.nom, 
					ctxt.client[ctxt.les_produits[i].client_sb].ident.nom, TAILLE_BUFFER);
			envoi_paquet(ctxt.les_produits[i].client_sb, mes);
		}
		else
		{
			mes.offre = PRODUIT_NON_ACHETE;
			mes.type = T_OBJET_NON_REMPORTE;
		}

		/** On envoit le paquet au vendeur. */
		envoi_paquet(ctxt.les_produits[i].vendeur, mes);
	}
	
	/** 
	 * On fini par leur envoyer le message de fin de transmission.
	 */
	mes.type = T_FIN_TRANSMISSION;
	envoyer_a_tous(mes);
}
void envoyer_paquet_aux_clients_bidder(message_s mes)
{
	int i;
	for(i = 0 ; i < NB_CLIENTS ; i++)
		if(ctxt.client[i].type == 1)
			envoi_paquet(i, mes);
}
void envoyer_a_tous(message_s mes)
{
	int i;
	for(i = 0 ; i < NB_CLIENTS ; i++)
	{
		if(ctxt.client[i].type == 1 || ctxt.client[i].fd != 0)
		{
			envoi_paquet(i, mes);
		}
	}
}
int est_autorise(message_s mes)
{
	FILE * fichier = NULL;
	char chaine[TAILLE_BUFFER * 2 +1];
	char tampon[TAILLE_BUFFER * 2 +1];

	bzero(chaine, TAILLE_BUFFER * 2 +1);
	bzero(tampon, TAILLE_BUFFER * 2 +1);

	snprintf(chaine, TAILLE_BUFFER * 2, "%s:%s", 
			mes.ident.nom, mes.ident.passwd);
	chaine[TAILLE_BUFFER * 2] = '\0';
	
	if((fichier = fopen(FICHIER_UTILISATEURS, "r")) == NULL)
		quitter("fopen");

	while(fgets(tampon, TAILLE_BUFFER * 2 + 1, fichier))
	{
		tampon[strlen(tampon) - 1] = '\0';
		if(strcmp(tampon, chaine) == 0)
		{
			fclose(fichier);
			return 0;
		}
	}

	fclose(fichier);
	return -1; // utilisateur non enregistré
}
void renvoi_erreur_connexion(message_s mes)
{
	mes.type = T_CONNEXION_REFUSEE;
	sendto(ctxt.udp_sock, (void *) &mes, sizeof(message_s), 0,
			(struct sockaddr *) &ctxt.addrtmp, ctxt.addrlen);
}
void recevoir_message_udp(message_s * mes)
{
	if(recvfrom(ctxt.udp_sock, mes, sizeof(message_s), 0,
				(struct sockaddr *) &ctxt.addrtmp, &ctxt.addrlen) == -1)
			quitter("réception paquet");
}
