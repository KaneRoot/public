import javax.swing.*;
import java.awt.Graphics;

public class Case extends JButton
{
	public boolean franchissable;
	public int num;
	public static final int TAILLE_X = 50;
	public static final int TAILLE_Y = 50;
	public Case(boolean x, int i)
	{
		this.num = i;
		this.franchissable = x;
	}
	public boolean isFranchissable()
	{
		return this.franchissable;
	}
	public void paint(Graphics g)
	{
		g.drawRect((this.num * TAILLE_X) % 5, (this.num * TAILLE_Y) % 7, TAILLE_X, TAILLE_Y);
		this.setSize(50,50);
	}
}
