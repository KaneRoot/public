package modele.elements;

import util.*;
import java.io.*;
import java.util.*;
import javax.imageio.ImageIO;


/**
 * Élément fixe.
 *
 */

public class E_fixe extends Element
{
	/**
	 * Constructeur.
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 * @param size : la taille du personnage.
	 * @param b : la forme de l'objet.
	 *
	 */
	public E_fixe(int x, int y, int size, Bounding b)
	{
		super(x,y,size);
		setBounding(new Bounding(new Rectangle(getPosition(),size+5,size)));

		try
		{
			addImage (ImageIO.read (new File("./image/fixe1.png")));
		}
		catch (IOException e)
		{
			//TODO
		}
		setEtat (PLEINEVIE);
	}

	/**
	 * Constructeur.
	 *
	 * @param x : la position sur l'axe des abscisses.
	 * @param y : la position sur l'axe des ordonnées.
	 * @param size : la taille du personnage.
	 *
	 */
	public E_fixe(int x, int y, int size)
	{
		this(x,y,size,null);
	}

	public E_fixe()
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
			collision();
			return true;
		}
		else
			return false;
	}
	
	/** @return une copie de l'élément fixe. */
	public Element copie ()
	{
		return new E_fixe (this.getPosition().getX(),
					this.getPosition().getY(),
					this.getSize(),
					this.getBounding());
	}
}
