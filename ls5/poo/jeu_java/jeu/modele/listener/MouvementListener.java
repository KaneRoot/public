package modele.listener;

import java.util.EventListener;
import modele.event.MouvementEvent;

/** Interface qui définie les méthodes pour être un écouteur de mouvement. */
public interface MouvementListener extends EventListener
{
	/** Avertisseur de mouvement */
	public void enMouvement(MouvementEvent event);
}
