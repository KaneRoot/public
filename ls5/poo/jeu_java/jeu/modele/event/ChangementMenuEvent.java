package modele.event;

import javax.swing.JPanel;

import modele.Map;

/**
 * Classe d'évènement qui permet de changer de Menu de .
 * 
 */

public class ChangementMenuEvent
{
	/**
	 * Les différentes options de changement de menu.
	 *
	 */
	public final static int PARTIE = 1;
	public final static int CONTINUER = 2;
	public final static int MENU_PRINCIPAL = 3;
	public final static int MENU_OPTIONS = 4;
	public final static int MENU_MAPS = 5;
	public final static int CHANGEMENT_MAP = 6;
	public final static int GAGNE = 7;
	public final static int PERDU = 8;

	/**
	 * Les variables
	 *
	 */
	public JPanel panneau_actuel = null;
	public int num_menu;
	public Map nouvelle_carte = null;

	/**
	 * Constructeur.
	 *
	 * @param jp : le panneau affiché actuellement (un menu).
	 * @param num_menu : le numéro du menu qu'on voudrait afficher.
	 *
	 */
	public ChangementMenuEvent(JPanel jp, int num_menu)
	{
		this.panneau_actuel = jp;
		this.num_menu = num_menu;
	}
	public Map getNouvelleCarte()
	{
		return nouvelle_carte;
	}
}
