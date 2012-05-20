package modele.elements;

import javax.imageio.ImageIO;
import java.io.*;
import java.util.*;


import util.Bounding;
import util.*;
import modele.elements.Element;


/**
 * Classe de l'élément qui peut tuer le personnage.
 *
 */

public class E_lethal extends Element
{
	/**
	 * Constructeur.
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 * @param size : la taille du personnage.
	 *
	 */
	public E_lethal (int x, int y, int size)
	{
		super (x,y,size);
		setBounding(new Bounding(new Rectangle(getPosition(),
						size,size)));
		try
		{
			addImage (ImageIO.read (new File("./image/lethal1.png")));
		}
		catch (IOException e)
		{	
			//TODO
		}

		setEtat (PLEINEVIE);
	}
	public E_lethal()
	{
		this(0,0,0);
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
		if  (bounding_.estEnCollision(el.getBounding()))
		{
			el.setEtat(el.getEtat()-10);
			collision();
			return true;
		}
		else
			return false;
	}

	/** @return une copie de l'élément E_lethal. */
	public Element copie ()
	{
		return new E_lethal (this.getPosition().getX(),
					this.getPosition().getY(),
					this.getSize());
	}

}
