package controleur.thread;

import util.Vector2f;
import modele.Map;
import modele.event.*;
import modele.listener.*;
import modele.elements.Element;
import controleur.ControlerMap;

/**
 * Thread qui gère le mouvement du personnage.
 *
 */
public class MouvementThread extends Thread implements CollisionListener
{
	private Map map_;
	private ControlerMap ctrlMap;
	private boolean born;
	private boolean repose;
	private boolean suspendre_;
	private boolean fin;
	private boolean collision_;	

	/**
	 * Constructeur.
	 * 
	 * @param m : la carte sur laquelle on joue.
	 *
	 */
	public MouvementThread (Map m,ControlerMap ctrl)
	{
		map_ = m;
		born = true;
		suspendre_ = false;
		repose = false;
		fin = false; 
		collision_ = false;
		ctrlMap = ctrl;		
	}
	
	/** Pour savoir si le jeu est en pause. */
	public boolean isPause(){return repose;}

	/** S'il est né (démarré). */
	public boolean isNouveauNe(){return born;}

	/** Permet de mettre fin à la partie. */
	public void finir() {fin = true;}
	
	/** Mettre le thread en pause. */
	private synchronized void pause() throws InterruptedException 
	{
		repose = true;
		wait();
	}
	
	/** Suspendre la partie. */
	public void suspendre(){suspendre_ = true;}
	
	/** Reprendre la partie. */
	public synchronized void reprendre()
	{
		notify();	
		if (suspendre_)
			suspendre_ = false;
	}

	/** Définir si on est en collision. */
	public void collision(boolean b){collision_ = b;}
	
	/** Lancement du thread. */
	public void run()
	{
		born = false;
		deplacement();
	}
	
	/** Savoir si on est sur le sol. */
	private boolean isOnSoil()
	{
		return (map_.getPerso().getPosition().getY() 
			== map_.getYSol(map_.getPerso().getPosition().getX()));
	}

	/**
	 * Savoir si on est sous le sol.
	 *
	 * Permet par la suite de remettre le personnage sur le sol 
	 * (on a manqué la collision avec le sol, on le replace).
	 *
	 */
	private boolean isUnderSoil()
	{
		return (map_.getPerso().getPosition().getY() 
			> map_.getYSol(map_.getPerso().getPosition().getX()));
	}
	
	/** 
	 * Calcul du déplacement.
	 *
	 */
	public void deplacement()
	{
		int x,y,yi;	
		Vector2f v_;
		while (!fin)
		{	
			v_ = map_.getPerso().getDx();	
			try
			{
				if ((!(((int)map_.getPerso().getDx().norme()) == 0) || !isOnSoil()) 
						&& !suspendre_ && (map_.getPerso().getPosition().getX()-5>0||map_.getPerso().getDx().getI()>0))
				{
					/*
					x = (int)(map_.getPerso().getPosition().getX()+v_.getI());
					y = (map_.getPerso().getPosition().getY()-v_.getJ()>=map_.getYSol(x)||isUnderSoil()?
						map_.getYSol(x):(int)(map_.getPerso().getPosition().getY()-v_.getJ()));
					//yi = y-map_.getPerso().getPosition().getY(); A utiliser plus tard
					map_.getPerso().setPosition(x,y);
					*/

					x = (int)(map_.getPerso().getPosition().getX()+(v_.getI()/2));
					y = (map_.getPerso().getPosition().getY()-v_.getJ()>=map_.getYSol(x)||isUnderSoil()?
						map_.getYSol(x):(int)(map_.getPerso().getPosition().getY()-v_.getJ()/2));
					//yi = y-map_.getPerso().getPosition().getY(); A utiliser plus tard
					map_.getPerso().setPosition(x,y);
					
					if (map_.getPerso().getDx().norme()>400)
					{
						map_.getPerso().setEtat(map_.getPerso().getEtat()-1);
						if (map_.getPerso().getEtat()<=Element.MORT)
						{
							ctrlMap.finPartie();
						}
					}
					
					if (!collision_)
					{
						map_.getPerso().setDx (map_.getPerso().getDx().getI()*.95f,
						(!isOnSoil()&&!collision_?(map_.getPerso().getDx().getJ()-
						(int)(map_.getMasse()*map_.getPerso().getMasse())/100):0f));
					}
					else
					{
						map_.getPerso().setDx(map_.getPerso().getDx().getI()*0.95f,0f);
					}
					sleep(20);
				}
				else
					pause();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}

	/** 
	 * Spécifier qu'on est en collision avec un objet.
	 * 
	 * @param event : la collision spécifiée par un évènement CollisionEvent.
	 *
	 */
	public void enCollision (CollisionEvent event)
	{
		if (map_.getPerso().getEtat()<=Element.MORT)
		{
			ctrlMap.finPartie();
		}
		collision_ = true;
	}


}
