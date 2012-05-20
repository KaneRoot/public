package vue;

import javax.swing.JPanel;

import controleur.ControlerMap;
import modele.listener.MouvementListener;
import modele.listener.CollisionListener;

/**
 * Classe VueMap qui reprend le concept MVC, les différentes vues l'implémentent.
 *
 */

@SuppressWarnings("serial")
public abstract class VueMap extends JPanel  implements MouvementListener
{
	private ControlerMap ctrl_;
	
	public VueMap (ControlerMap ctrl)
	{
		super();
		ctrl_ = ctrl;
	}

	public ControlerMap getControler()
	{
		return ctrl_;
	}
	
	
}
