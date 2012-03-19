import javax.swing.*;
import java.awt.Graphics;
import java.awt.Color;

public class Case
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
}
