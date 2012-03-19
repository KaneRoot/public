import javax.swing.*;

public class Case extends JButton
{
	public boolean franchissable;
	public Case(boolean x)
	{
		this.franchissable = x;
		this.setSize(50,50);
	}
	public boolean isFranchissable()
	{
		return this.franchissable;
	}
}
