package modele.listener;

import java.util.EventListener;
import modele.event.PartieEvent;


/** Interface qui définie les méthodes nécessaires pour un écouteur de partie. */
public interface PartieListener extends EventListener
{
	public void partie (PartieEvent event);
}
