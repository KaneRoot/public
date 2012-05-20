package controleur;

import java.awt.KeyboardFocusManager;
import javax.swing.JPanel;
import javax.swing.JFrame;
import java.util.ArrayList;
import javax.swing.JLabel;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

import vue.menu.Menu;
import util.*;
import modele.*;
import modele.event.*;
import modele.elements.*;
import vue.*;
import vue.menu.*;
import controleur.thread.*;

/**
 * Classe ControleurMenu, la classe principale du jeu.
 *
 */

public class ControleurMenu 
{
	/** JPanel du menu affiché à l'accueil. */
	public Menu jp_menu = null ;

	/** JPanel dans lequel on affiche le jeu. */
	public JPanel jp_partie = null ;

	/** JPanel du menu du choix des cartes. */
	public JPanel jp_maps = null ;

	/** Frame du jeu. */
	public JFrame jf_jeu = null ;

	/** Controleur de la vue INGAME. */
	public ControlerMap ctrlMap = null ;

	/** Carte par défaut. */
	public Map carte_courante = new ChargementMap("./maps/FichierValable").getMap();

	/** répertoire par défaut des cartes. */
	public static final String repertoire_cartes = "./maps";

	/**
	 * Constructeur par défaut du Contrôleur.
	 *
	 * Crée la JFrame et le menu.
	 */

	public ControleurMenu()
	{
		this.jf_jeu = new JFrame();
		// this.jf_jeu.setSize(1000,500);
		this.jp_menu = new Menu(this);

		/*
		this.jp_menu.setSize(1000,500);
		this.jp_menu.repaint();
		this.jf_jeu.repaint();
		*/
	}

	/**
	 * Lance le programme.
	 * Ajoute le menu à la Frame principale.
	 */
	public void go()
	{
		this.jf_jeu.add(jp_menu);
		this.jf_jeu.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.jf_jeu.pack();
		this.jf_jeu.setVisible(true);
	}

	/**
	 * Démarrage de la partie.
	 *
	 */
	private void startPartie()
	{
		this.ctrlMap = new ControlerMap(this.carte_courante, this);
		this.ctrlMap.go();
		this.jp_partie = ctrlMap.getVue();
		this.jf_jeu.add(this.jp_partie);
		this.jp_partie.requestFocus();	
		this.jf_jeu.setSize(1000,500);	
		this.ctrlMap.getVue().setSize(1000,500);
		
		this.jp_partie.setVisible(true);
	}

	/**
	 * Pour continuer la partie après une pause.
	 *
	 */

	private void resumePartie()
	{
		if(this.jp_partie == null)
			startPartie();
		else
		{
			this.reprendrePartie();
			this.jp_partie.setVisible(true);
			this.jp_partie.requestFocus();	
		}
	}

	/**
	 * Pour changer d'interface.
	 *
	 */

	public void changerPanneau(ChangementMenuEvent e)
	{
		if(e.panneau_actuel != null)
			e.panneau_actuel.setVisible(false);
		else
			System.out.println("Il y a un soucis : panneau_actuel à null");

		switch(e.num_menu)
		{
			case ChangementMenuEvent.PARTIE :
				startPartie();
				break;
			case ChangementMenuEvent.MENU_PRINCIPAL :
				this.jp_menu.setVisible(true);
				if(this.ctrlMap != null)
					this.mettreEnPause();
				break;
			case ChangementMenuEvent.CONTINUER :
				resumePartie();
				break;
			case ChangementMenuEvent.MENU_MAPS :
				choixMap();
				break;
			case ChangementMenuEvent.CHANGEMENT_MAP :
				this.carte_courante = e.getNouvelleCarte();
				startPartie();
				break;
			case ChangementMenuEvent.GAGNE :
				// e.panneau_actuel.setVisible(true);
				this.jp_menu.setMessage("GAGNÉ");
				this.jp_menu.setVisible(true);
				break;
			case ChangementMenuEvent.PERDU :
				// e.panneau_actuel.setVisible(true);
				this.jp_menu.setMessage("PERDU");
				this.jp_menu.setVisible(true);
				break;

			default :
				System.out.println("soucis au niveau du changement de menu");
				break;
		}
		this.jf_jeu.repaint();
	}

	/** Méthode pour simplifier la compréhension du code. */
	private  void reprendrePartie() { this.ctrlMap.reprendre(); }

	/** Méthode pour simplifier la compréhension du code. */
	private void mettreEnPause() { this.ctrlMap.suspendre(); }

	/** Affichage du menu de choix de la carte. */
	private void choixMap()
	{
		if(this.jp_maps == null)
		{
			this.jp_maps = new MenuCartes(this, repertoire_cartes);
			this.jf_jeu.add(jp_maps);
		}

		this.jp_maps.setVisible(true);
	}
}
