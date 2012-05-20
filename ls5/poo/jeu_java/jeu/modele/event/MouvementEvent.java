package modele.event;

import java.util.EventObject;
import util.Vector2f;

/**
 * Pour prévenir que le joueur se déplace.
 *
 */
@SuppressWarnings("serial")
public class MouvementEvent extends EventObject 
{
	private Vector2f v_;
	
	public MouvementEvent(Object source, Vector2f v)
	{
		super(source);
		setVector(v);
	}

	/** défini le vecteur de position du joueur. */
	public void setVector(Vector2f v) { this.v_ = v; }

	/** retourne le vecteur qui défini la position du joueur. */
	public Vector2f getVector() { return v_; }

}
