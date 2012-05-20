package modele.event;

import util.Vector2f;
import java.util.EventObject;

/** 
 * Classe évènement qui sert à envoyer les informations à la vue sur la collision du personnage à un objet. 
 *
 */
public class CollisionEvent extends EventObject
{
	private Vector2f v_;

	public CollisionEvent (Object source, Vector2f v)
	{
		super(source);
		v_ = v;
	}

	/** @return vecteur de collision. */
	public Vector2f getVector() { return v_; }
}
