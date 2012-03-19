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

		this.setSize(c.ty*100, c.tx*100);
	}
	@Override
	public void paint(Graphics g)
	{
		super.paintComponent(g);
		Case[] cases = c.getCases();
		for(Case mcase : cases)
		{
			if(mcase.isFranchissable())
				g.setColor(Color.green);
			else
				g.setColor(Color.red);

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
