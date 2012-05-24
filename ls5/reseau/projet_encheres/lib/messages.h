/**
 * @file messages.h
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
 * Ce fichier contient les messages affichés à l'écran.
 */
#ifndef __MESSAGES_H__
#define __MESSAGES_H__


const char * m_demande_prix = 
"Veuillez entrer la somme que vous êtes prêt à dépenser pour ce produit : ";
const char * m_mauvais_type = 
"Vous avez entré ou reçu un message avec un type non défini correctement\n";
const char * m_ligne_vide = 
"\033[36m ----------------------------------------------------- \033[00m \n";

const char * m_connexion_par_defaut = 
"Vous n'avez entré aucun paramètre.\n"
"Connexion par défaut en local et sur le port 9000\n";

const char * m_demande_action_seller =
"\n"
"1. Démarrer les enchères.\n"
"2. Consulter les offres actuelles.\n"
"3. Ajouter un (ou plusieurs) produit.\n";

const char * m_demande_action = 
"\n"
"1. Demander les produits.\n"
"2. Faire une offre.\n"
"3. Demander l'objet courant.\n";

const char * m_produit_suivant =
"\n\n\033[36m Nous passons au produit suivant.\033[00m \n";
const char * m_debut_prog =  
"Début du programme. \033[36mPour quitter : ^D\033[00m \n";


const char * message_envoi_objets = 
"À partir d'ici nous allons envoyer des objets. "
"\033[31mAppuyez sur ^D pour finir.\033[00m\n";
const char * m_connexion_v6 = "Connexion d'une personne en IP v6.\n";
const char * m_connexion_v4 = "Connexion d'une personne en IP v4.\n";

const char * m_sender_nom_objet = "Veuillez entrer le nom de l'objet à envoyer : ";
const char * m_sender_prix_depart = "Veuillez entrer son prix de départ : ";
const char * m_sender_prix_minimal = "Veuillez entrer le prix minimum à atteindre : ";
const char * m_demande_nom = "Votre nom : ";
const char * m_demande_pass = "Votre mot de passe : ";
const char * m_reception_message = "\033[36m####\033[00m ";
const char * m_encheres_non_demarrees = 
"\033[31m\tIl manque des participants pour les enchères !\033[00m \n";

const char * m_sortie_programme = 
"\033[36mLe programme se termine.\033[00m\n";

char * m_err_reception_offre_encheres_non_debutees = 
"\033[31mLes enchères n'ont pas débutées.\033[00m ";
char * m_err_reception_offre_num_produit =
"\033[31mOffre non valable : objet non valide.\033[00m";
char * m_err_reception_offre_num_objet =
"\033[31mNous n'en sommes pas (plus) à l'enchère de cet objet.\033[00m";

const char * m_fin_encheres =
"\033[32m\tCeci marque la fin des enchères !\033[00m \n";
const char * m_debut_encheres =
"\033[32m\tCeci marque le début des enchères !\033[00m \n";

#endif

