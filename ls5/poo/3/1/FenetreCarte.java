import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Créée un PanneauCarte et l'ajoute au contenu de la fenêtre
 *
 **/
public class FenetreCarte extends JFrame
{
	private PanneauCarte panneau;
	private Carte c;

	public void Afficher(Carte c)
	{
		this.c = c;
		this.panneau = new PanneauCarte(c);
		this.add(this.panneau);

		setVisible(true);
		this.pack();
		setSize(c.ty * 50, c.tx * 50);
	}
	public FenetreCarte()
	{
		super();
		build();
	}
	private void build()
	{
		setTitle("Premier Exercice");
	//	setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
