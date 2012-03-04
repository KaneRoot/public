import javax.swing.text.*;
import javax.swing.event.*;

class JTPEcouteur implements DocumentListener
{
	JTPersonne popa;
	
	public JTPEcouteur(JTPersonne parent)
	{
		this.popa = parent;
	}
	public void insertUpdate(DocumentEvent e)
	{
		this.popa.miseAJour();
	}
	public void removeUpdate(DocumentEvent e)
	{
		this.popa.miseAJour();
	}
	public void changedUpdate(DocumentEvent e)
	{
		this.popa.miseAJour();
	}
}
