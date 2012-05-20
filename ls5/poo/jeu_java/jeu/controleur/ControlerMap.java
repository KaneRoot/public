package controleur;

import controleur.thread.MouvementThread;
import controleur.thread.CollisionThread;

import modele.elements.*;
import util.Vector2f;
import modele.*;
import vue.*;
import vue.Vue;
import modele.event.*;


/**
 * Suivant le modèle MVC, cette classe est le contrôleur de la partie (in game).
 *
 */
public class ControlerMap
{
	private MouvementThread thread1;
	private CollisionThread thread2;
	private Map map = null;
	private Vue vue = null;
	private ControleurMenu ctrlMenu;
	
	/**
	 * @param m : la carte que l'on manipule, sur laquelle on joue.
	 * @param c : le contrôleur du menu (changement de menus etc.
	 */
	public ControlerMap(Map m, ControleurMenu c)
	{
		map = m;
		ctrlMenu = c;
		vue = new Vue(this,map.getPerso().getPosition().getX(),
				map.getPerso().getPosition().getY());
		map.ajouterEcouteurMouvement(vue);

		thread1 = new MouvementThread(map,this);
		thread2 = new CollisionThread(map,thread1);

		map.getPerso().ajouterEcouteurMouvement(vue);
		map.getPerso().ajouterEcouteurCollision(thread1);
	
		for (int i=0; i<map.nbElem();i++)
		{
			map.getElem(i).ajouterEcouteurCollision (thread1);
		}

		thread2.start();
	}

	/** @return le contrôleur de menu. */
	public ControleurMenu getCtrlMenu() { return ctrlMenu; }

	/** @return la carte sur laquelle on joue. */
	public Map getMap() { return map; }
	/** @return la vue associée à ce contrôleur (qui gère l'affichage du jeu). */
	public Vue getVue() { return vue; }
	/** Permet de mettre en pause le jeu. */
	public void suspendre() { thread1.suspendre(); } 
	/** Permet de reprendre le jeu après une pause. */
	public void reprendre() { thread1.reprendre(); } 
	/** Renvoie l'état des thread du controleur */
	public boolean isPause() { return thread1.isPause(); } 

	/** Affiche la vue. */
	public void go() { vue.setVisible(true); }


	public void finPartie()
	{
		thread1.finir();
		thread2.finir();
		if (map.getPerso().getSac().size() >= map.getBut() && map.getPerso().getEtat() > Element.MORT)
		{
			ctrlMenu.changerPanneau(new ChangementMenuEvent(vue, 
						ChangementMenuEvent.GAGNE));
		}
		else
		{
			ctrlMenu.changerPanneau(new ChangementMenuEvent(vue, 
						ChangementMenuEvent.PERDU));
		}
	}

	/** 
	 * Notifie le mouvement enregistré par la vue. 
	 *
	 * Détecte si on gagne ou si on perd la partie.
	 *
	 * */
	public void notifierMouvement(Vector2f v)
	{	
		if (map.getArrivee() <= map.getPerso().getPosition().getX() ||
					 map.getPerso().getEtat() == Element.MORT)
		{
			finPartie();
		}
		else
		{
			map.getPerso().getDx().add(v);
			if (thread1.isNouveauNe())
				thread1.start();
			else if (thread1.isPause())
				thread1.reprendre();
		}
	}
}
