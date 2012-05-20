package modele.listener;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import vue.menu.*;
import modele.event.*;
import controleur.*;
import modele.*;

/**
 * Écouteur de bouton.
 *
 * Permet de choisir une carte.
 */
public class JBMapListener implements ActionListener
{
	ControleurMenu c;
	MenuCartes m;
	Map carte;

	/**
	 * @param c : le contrôleur de menu.
	 * @param m : le menu des cartes.
	 * @param carte : la carte sur laquelle on veut jouer.
	 */
	public JBMapListener(ControleurMenu c, MenuCartes m, Map carte)
	{
		this.c = c;
		this.m = m;
		this.carte = carte;
	}
	
	/**
	 * Lancement d'un évènement de changement de panneau à afficher (le jeu).
	 * Avec la carte choisie.
	 *
	 */
	public void actionPerformed(ActionEvent e)
	{
		ChangementMenuEvent event;
		event = new ChangementCarteEvent(m, ChangementMenuEvent.CHANGEMENT_MAP, carte);
		this.c.changerPanneau(event);
	}
}
