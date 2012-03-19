import javax.swing.*;

public class Carte
{
	Case[] c;
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

		for(i = 0 ; i < (x*y) ; i++)			
			this.c[i] = new Case(true,i);
		this.c[8].franchissable = false;
		this.c[15].franchissable = false;

	}
	public void Afficher()
	{
		FenetreCarte f = new FenetreCarte();
		f.Afficher(this);
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
				c.Afficher();
			}
		});
	}
}
