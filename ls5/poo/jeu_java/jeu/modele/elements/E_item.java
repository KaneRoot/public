package modele.elements;


import util.Ellipse;
import util.Bounding;

/**
 * Objet que l'on peut attraper.
 *
 */
public class E_item extends Element
{
	/**
	 * Constructeur.
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 * @param size : la taille du personnage.
	 *
	 */
	public E_item (int x, int y, int size)
	{
		super (x,y,size);
		setBounding(new Bounding(new Ellipse(getPosition(),size,size)));
		setEtat (ATTRAPABLE);
	}

	public E_item ()
	{
		this (0,0,0);
	}
	
	/** 
	 * Informe si cet élément en collision avec l'objet X.
	 *
	 * @param el : l'élément que l'on cherche à déterminer s'il est 
	 * en collision avec cet objet.
	 *
	 */
	public boolean entreEnCollision(Element el)
	{
		if  (bounding_.estEnCollision(el.getBounding())&&this.getEtat()==ATTRAPABLE)
		{
			el.attrape (this);
			this.setEtat(ATTRAPER);
			collision();
			return true;
		}
		else
			return false;
	}

	/** @return une copie de l'item. */
	public Element copie()
	{
		return new E_item (getPosition().getX(),getPosition().getY(),getSize());
	}
}
