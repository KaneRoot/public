package modele.listener;

import vue.menu.Menu;
import modele.event.ChangementMenuEvent;
import controleur.ControleurMenu;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class JBMapChoiceListener implements ActionListener
{
	ControleurMenu c;
	Menu m;

	public JBMapChoiceListener(ControleurMenu c, Menu m)
	{
		this.c = c;
		this.m = m;
	}
	public void actionPerformed(ActionEvent e)
	{
		ChangementMenuEvent event = new ChangementMenuEvent(m, ChangementMenuEvent.MENU_MAPS);
		this.c.changerPanneau(event);
	}
}
