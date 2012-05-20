package modele.listener;

import vue.menu.Menu;
import modele.event.ChangementMenuEvent;
import controleur.ControleurMenu;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * Écouteur du bouton qui fait le lancement d'une nouvelle partie.
 *
 */
public class JBStartGameListener implements ActionListener
{
	ControleurMenu c;
	Menu m;

	/**
	 * @param c : le contrôleur de menu.
	 * @param m : le menu.
	 */
	public JBStartGameListener(ControleurMenu c, Menu m)
	{
		this.c = c;
		this.m = m;
	}

	/**
	 * Déclenche un changement de menu et donc le lancement du jeu.
	 *
	 */
	public void actionPerformed(ActionEvent e)
	{
		ChangementMenuEvent event = new ChangementMenuEvent(m, ChangementMenuEvent.PARTIE);
		this.c.changerPanneau(event);
	}
}
