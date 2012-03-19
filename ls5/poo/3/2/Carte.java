import javax.swing.*;

public class Carte
{
	Case[] c;
	Chemin ch;
	/*
	 * Créée une FenetreCarte et affiche la topologie de la carte
	 *
	 **/
	public int tx,ty;
	public Carte(int x, int y)
	{
		int i;
		this.tx = x;
		this.ty = y;
		this.c = new Case[x*y];
		this.ch = new Chemin();

		for(i = 0 ; i < (x*y) ; i++)			
			this.c[i] = new Case(true,i);
		this.c[10].franchissable = false;
		this.c[17].franchissable = false;
		this.c[24].franchissable = false;

		this.ch.ajouterCase(c[14]);
		this.ch.ajouterCase(c[20]);

	}
	public void AfficherChemin()
	{
		FenetreCarte f = new FenetreCarte();
		f.AfficherChemin(this, this.ch);
	}
	public Case[] getCases()
	{
		return this.c;
	}
	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				Carte c = new Carte(5,7);
				c.AfficherChemin();
			}
		});
	}
}
