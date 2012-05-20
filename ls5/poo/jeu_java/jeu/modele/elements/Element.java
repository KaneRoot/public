package modele.elements;

import java.util.ArrayList;
import java.awt.image.BufferedImage;

import util.*;
import modele.event.CollisionEvent;
import modele.listener.CollisionListener;


/**
 * La classe dont tous les éléments dérivent.
 *
 * Permet de définir un élément.
 */

public abstract class Element
{
	/**
	*  Champs static décrivant l'etat de l'élement
	**/
	public static int MORT = 0;
	public static int ATTRAPABLE = -2;
	public static int ATTRAPER = -3;
	public static int INVISIBLE = -1;
	public static int INVINCIBLE = -10;
	public static int PLEINEVIE = 100;


	/**
	*  Champs en mode protected; décrivant les proprietes de l'element
	**/
	protected Point2d x_;			// Position de l'élement
	protected int size_;			// Taille de l'élement
	protected Bounding bounding_;		// Zone d'influence
	protected float masse_;

	protected ArrayList<CollisionListener> collisionEcouteurs_; // Ecouteurs d'évenement
	protected ArrayList<BufferedImage> image;
	protected ArrayList<Element> sac;

	protected int currentImage;
	protected int etat;
	
	public Element(Point2d p, int size, Bounding b)
	{		
		this (p,size,b,new ArrayList<BufferedImage>(1));
	}

	public Element(Point2d p, int size, Bounding b, ArrayList<BufferedImage> im)
	{
		collisionEcouteurs_ = new ArrayList<CollisionListener>(1);
		x_ = p;
		bounding_ = b;
		size_ = size;
		image = im;
		currentImage = 0;
		sac = new ArrayList<Element>(1);
		masse_ = 1f;
	}

	/**
	* @param CollisionListener cl 
	* @see Permets de 
	**/
	public void ajouterEcouteurCollision(CollisionListener cl)
	{
		collisionEcouteurs_.add(cl);
	}	

	public void envleverEcouteurCollision(CollisionListener cl)
	{
		collisionEcouteurs_.remove(cl);
	}

	public Element(int x, int y, int size)
	{
		this(new Point2d(x,y), size, null);
	}

	/**
	 * Constructeur par défaut.
	 *
	 * Il est appelé lorsqu'on crée l'élément dans le fichier de configuration.
	 *
	 * Puis on appellera d'autres méthodes pour changer la taille et 
	 * l'emplacement de l'objet.
	 *
	 */
	public Element()
	{
		this(0,0,0);
	}

	/** Définir la position de l'objet sur la carte. */
	public void setPosition(int x, int y) 
	{
		this.x_.setX(x);
		this.x_.setY(y);
	}

	/** @return la position (coordonnée des abscisses). */
	public Point2d getPosition() { return x_; }

	/** 
	 * Défini la taille de l'élément. 
	 *
	 * @param size : la taille de l'élément.
	 *
	 */
	public void setSize(int size)
	{
		this.size_ = size;
		setBounding(new Bounding(new Rectangle(x_,size_,size_)));
	}

	/** @return la taille de l'élément. */
	public int getSize() { return size_; }
	
	public void setBounding(Bounding b) { bounding_ = b; }
	
	/** @return le type d'objet. */
	public Bounding getBounding() { return bounding_; }

	/** Défini l'image de l'objet. */
	public void addImage (BufferedImage im) { image.add (im); }

	/** @return l'énième image liée à cet élément. */
	public BufferedImage getImage (int i) { return image.get (i); }
	
	/** @return le nombre d'images. */
	public int nbImage () { return image.size(); }

	/** @return l'image courante. */
	public int getCurrentImage() { return currentImage; }
	
	/** Défini l'image courante. */
	public void setCurrentImage(int c) { currentImage = c; }

	/** Défini le poid de l'element */
	public void setMasse(float m) { masse_ = m; }
	
	/** Renvoi le poid de l'element */
	public float getMasse() { return masse_; }

	/** 
	 * À redéfinir dans chaque classe, indique si on est en collision avec un autre élément. 
	 */
	public abstract boolean entreEnCollision(Element el);
	
	public void collision()
	{	
		for (int i=0;i<collisionEcouteurs_.size();i++)
			collisionEcouteurs_.get(i).enCollision(new CollisionEvent(this,
					new Vector2f (getPosition().getX(),getPosition().getY())));
	}

	/** @return l'état de l'élément. */
	public int getEtat() { return etat; } 	
	
	/** @param etat : l'état de l'objet. */
	public void setEtat(int etat) { this.etat = etat; }	

	/** @return le sac d'éléments. */
	public ArrayList<Element> getSac() { return sac; }
	
	/** Attraper un élément. On l'ajoute au sac. */
	public void attrape (Element e) { sac.add (e); }

	public int nbElemAttrap () { return sac.size(); }

	/**
	 * Définir les différentes options.
	 *
	 * @param options Ce sont les options indiqués dans le fichier de configuration.
	 */
	public void setOptions (String[] options)
	{
		/*for (String s:options)
		{	
			if (s.compareTo (""))
			{
			}
			else if 
		}
		*/
	}
	
	public abstract Element copie();

}
