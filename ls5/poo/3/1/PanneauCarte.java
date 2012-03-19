import javax.swing.*;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Graphics;

public class PanneauCarte extends JPanel
{
	public Carte c;
	public PanneauCarte(Carte c)
	{
		this.c = c;
		this.setBackground(Color.black);
		this.setLayout(new GridLayout(this.c.tx, this.c.ty));
	}
	/*
	 * Redéfinition de paint pour dessiner la carte
	 *
	 **/
	@Override
	public void paint(Graphics g)
	{
		Case[] cases = this.c.getCases();

		for(int i = 0 ; i < (this.c.tx * this.c.ty) ; i++)
		{
			if(! cases[i].isFranchissable())
				cases[i].setBackground(Color.black);
			this.add(cases[i]);
			cases[i].repaint();
		}
	}
}
