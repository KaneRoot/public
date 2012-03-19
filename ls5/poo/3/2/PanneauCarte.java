import javax.swing.*;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Graphics;

public class PanneauCarte extends JPanel
{
	public Carte c;
	public Chemin ch;
	public PanneauCarte(Carte c, Chemin ch)
	{
		this.c = c;
		this.ch = ch;
		this.setBackground(Color.black);
		this.setSize(c.ty*100, c.tx*100);
	}
	@Override
	public void paint(Graphics g)
	{
		super.paintComponent(g);
		Case[] cases = c.getCases();
		for(Case mcase : cases)
		{
			if(this.ch.faitPartieDuChemin(mcase))
				g.setColor(Color.blue);
			else if(mcase.isFranchissable())
				g.setColor(Color.green);
			else
				g.setColor(Color.black);

			System.out.println("num : " + mcase.num + " taille x " + Case.TAILLE_X +
					" taille y " + Case.TAILLE_Y + " tx " + this.c.tx + " ty " +
					this.c.ty);
			g.fillRect(	
						(mcase.num % this.c.ty) * Case.TAILLE_X, 
						(mcase.num / this.c.ty) * Case.TAILLE_Y, 
						Case.TAILLE_X, 
						Case.TAILLE_Y);
		}
	}
}
