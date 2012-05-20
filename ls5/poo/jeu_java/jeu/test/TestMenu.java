package test;

import controleur.*;
import modele.*;
import modele.event.*;
import modele.listener.*;
import vue.*;
import vue.menu.*;


/**
 * Actuellement la classe qui démarre le jeu.
 *
 */
public class TestMenu
{
	/**
	 * Le main sert à lancer une instance de ControleurMenu qui est la classe principale.
	 *
	 */

	public static void main(String[] args)
	{
		ControleurMenu c = new ControleurMenu();
		c.go();
	}
}
