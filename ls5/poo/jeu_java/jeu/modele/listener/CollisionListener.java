package modele.listener;

import java.util.EventListener;
import modele.event.CollisionEvent;


/** interface qui défini les classes nécessaires pour être un écouteur de collision. */
public interface CollisionListener extends EventListener
{
	/** Avertisseur de collision */
	public void enCollision(CollisionEvent event);
}
