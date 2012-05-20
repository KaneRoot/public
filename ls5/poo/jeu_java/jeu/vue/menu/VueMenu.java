package vue.menu;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import controleur.ControleurMenu;

/**
 * Classe étendue par tous les différents panneaux de menu (options, choix map…)
 *
 */

public class VueMenu extends JPanel
{
	private ControleurMenu c;

	/**
	 * @param c : Le contrôleur du menu.
	 */

	public VueMenu(ControleurMenu c)
	{
		super();
		this.c = c;
	}

	/** 
	 * @return Le contrôleur du menu. 
	 *
	 */
	public ControleurMenu getControleur()
	{
		return this.c;
	}
}
