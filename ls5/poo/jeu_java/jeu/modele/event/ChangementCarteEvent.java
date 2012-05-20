package modele.event;

import javax.swing.JPanel;

import modele.Map;
import modele.event.*;

/**
 * Cette classe est liée au modèle MVC.
 *
 * Elle permet de créer un évènement de changement de carte, 
 * lorsqu'on sélectionne une carte dans le menu prévu à cet effet par exemple.
 *
 */
public class ChangementCarteEvent extends ChangementMenuEvent
{
	/**
	 * Les variables
	 *
	 */
	public Map nouvelle_carte;
	/**
	 * Le constructeur.
	 *
	 * @param jp : le JPanel qui a appelé cet évènement.
	 * @param num_menu : le numéro du menu que l'on cherche à atteindre.
	 * @param m : la carte sur laquelle on cherche à jouer.
	 *
	 */
	public ChangementCarteEvent(JPanel jp, int num_menu, Map m)
	{
		super(jp, num_menu);
		this.nouvelle_carte = m;
	}
	/** 
	 * Retourne la carte. 
	 *
	 * @return la carte sélectionnée.
	 *
	 */
	public Map getNouvelleCarte()
	{
		//return nouvelle_carte.copie();
		return nouvelle_carte;
	}
}
