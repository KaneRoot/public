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
	private Chemin ch;

	public void AfficherChemin(Carte c, Chemin ch)
	{
		this.c = c;
		this.ch = ch;
		this.panneau = new PanneauCarte(c, ch);
		this.add(this.panneau);

		setVisible(true);
		this.pack();
		setSize(c.ty * 50, c.tx * 50);
	}
	public void Afficher(Carte c)
	{
		this.AfficherChemin(c, this.ch);
	}
	public FenetreCarte()
	{
		super();
		build();
	}
	private void build()
	{
		setTitle("Second Exercice");
	//	setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
