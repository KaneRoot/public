package modele.listener;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import vue.menu.VueMenu;
import modele.event.ChangementMenuEvent;
import controleur.ControleurMenu;

/**
 * Écouteur du bouton "retour" pour revenir au menu principal.
 *
 */
public class JBRetourMenuListener implements ActionListener
{
	ControleurMenu c;
	VueMenu m;

	/**
	 * @param c : le contrôleur de menu.
	 * @param m : le menu.
	 */

	public JBRetourMenuListener(ControleurMenu c, VueMenu m)
	{
		this.c = c;
		this.m = m;
	}
	public void actionPerformed(ActionEvent e)
	{
		ChangementMenuEvent event = new ChangementMenuEvent(m, ChangementMenuEvent.MENU_PRINCIPAL);
		this.c.changerPanneau(event);
	}
}
