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

		for(i = 0 ; i < (x*y) - 20 ; i++)
			this.c[i] = new Case(true);
		for(i = (x*y) - 20; i < (x*y) - 10 ; i++)
			this.c[i] = new Case(false);
		for(i = (x*y) - 10; i < (x*y) ; i++)
			this.c[i] = new Case(true);

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
		Carte c = new Carte(5,7);
		c.Afficher();
		/*
		SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				Carte c = new Carte(5,7);
				c.Afficher();
			}
		});
		*/
	}
}
