import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FenetreCarte extends JFrame
{
	/*
	 * Créée un PanneauCarte et l'ajoute au contenu de la fenêtre
	 *
	 **/
	private PanneauCarte panneau;
	private Carte c;

	public void Afficher(Carte c)
	{
		this.c = c;
		this.panneau = new PanneauCarte(c);
		this.add(this.panneau);

		setSize(c.ty * 100, c.tx * 100);
		setVisible(true);
		this.pack();
	}
	public FenetreCarte()
	{
		super();
		build();
	}
	private void build()
	{
		setTitle("Premier Exercice");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
