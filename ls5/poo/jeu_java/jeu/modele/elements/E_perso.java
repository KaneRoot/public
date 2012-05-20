package modele.elements;

import modele.event.MouvementEvent;
import modele.listener.MouvementListener;
import util.*;
import java.util.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.*;

/**
 * Classe du personnage.
 *
 */
public class E_perso extends Element
{
	private Vector2f dx; // Vecteur vitesse
	private ArrayList<MouvementListener> mouvementEcouteurs_;	

	/**
	 * Constructeur.
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 * @param size : la taille du personnage.
	 *
	 */
	public E_perso (int x,int y, int size)
	{
		super(x,y,size);

		try
		{
			addImage (ImageIO.read (new File("./image/stik_walk1.png")));
			addImage (ImageIO.read (new File("./image/stik_walk2.png")));
			addImage (ImageIO.read (new File("./image/stik_walk3.png")));
			addImage (ImageIO.read (new File("./image/stik_walk4.png")));
			addImage (ImageIO.read (new File("./image/stik_fire1.png")));
			addImage (ImageIO.read (new File("./image/stik_fire2.png")));
			addImage (ImageIO.read (new File("./image/stik_fire3.png")));
			addImage (ImageIO.read (new File("./image/stik_fire4.png")));


		}
		catch (IOException e)
		{
			// TODO Message erreur	
		}
		
		mouvementEcouteurs_ = new ArrayList<MouvementListener>(1);
		dx = new Vector2f();
		setBounding(new Bounding(new Ellipse(x_,30,40)));
		setEtat (PLEINEVIE);
	}
	
	public E_perso ()
	{
		this (0,0,0);
	}

	public void ajouterEcouteurMouvement(MouvementListener ml)
	{
		mouvementEcouteurs_.add(ml);
	}
	
	public void enleverEcouteurMouvement(MouvementListener ml)
	{
		mouvementEcouteurs_.remove(ml);
	}
	
	/** 
	 * Défini le vecteur de vitesse du personnage. 
	 *
	 * @param vi : le vecteur sur l'axe des abscisses.
	 * @param vj : le vecteur sur l'axe des ordonnées.
	 *
	 */
	public void setDx(float vi, float vj) 
	{
		dx.setI(vi);
		dx.setJ(vj);
	}
	
	/** 
	 * Défini la position du personnage. 
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 *
	 */
	public void setPosition(int x, int y) 
	{
		this.x_.setX(x);
		this.x_.setY(y);
		mouvement();
	}

	/** @return le vecteur de vitesse du personnage. */
	public Vector2f getDx() 
	{
		return dx;
	}
	
	/** 
	 * Informe si le personnage entre en collision avec l'objet X.
	 *
	 * @param el : l'élément que l'on cherche à déterminer s'il est 
	 * en collision avec le personnage.
	 *
	 */
	public boolean entreEnCollision(Element el)
	{

		if  (bounding_.estEnCollision(el.getBounding()))
		{
			collision();
			return true;
		}
		else
			return false;
	}


	/** Déclenche evenement mouvement **/
	private void mouvement()
	{
        	for (int i=0;i<mouvementEcouteurs_.size();i++)
        		mouvementEcouteurs_.get(i).enMouvement(new MouvementEvent(this, 
						new Vector2f(getPosition().getX(),
						 getPosition().getY())));
	}

	/**
	 * @return une copie du personnage.
	 *
	 */
	public Element copie ()
	{
		E_perso e = new E_perso (getPosition().getX(), getPosition().getY(), getSize());
		e.setDx(getDx().getI(),getDx().getJ());
		return e;
	}

}
