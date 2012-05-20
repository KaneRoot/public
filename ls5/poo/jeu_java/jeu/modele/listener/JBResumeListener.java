package modele.listener;

import vue.menu.Menu;
import modele.event.ChangementMenuEvent;
import controleur.ControleurMenu;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Écouteur du bouton "continuer" pour continuer la partie en cours.
 *
 */
public class JBResumeListener implements ActionListener
{
	ControleurMenu c;
	Menu m;

	/**
	 * @param c : le contrôleur de menu.
	 * @param m : le menu.
	 */

	public JBResumeListener(ControleurMenu c, Menu m)
	{
		this.c = c;
		this.m = m;
	}
	public void actionPerformed(ActionEvent e)
	{
		ChangementMenuEvent event = new ChangementMenuEvent(m, ChangementMenuEvent.CONTINUER);
		this.c.changerPanneau(event);
	}
}
