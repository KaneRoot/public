// Ecouteurs de Loto1

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class IL_Cocher implements ItemListener
	// ecouteur des cases à cocher
{
   private Loto1 loto;
	
	public void itemStateChanged(ItemEvent e)
	{
	// on peut savoir directement si le bouton a été selectionne ou deselectionne
	   this.loto.cocher(e.getStateChange() == ItemEvent.SELECTED);
	}
	//constructeur:
	public IL_Cocher (Loto1 lol)
	{
	  this.loto=lol;
	}
}

class AL_jtf implements ActionListener
	// ecouteur du jtf de saisie de chiffres
{
   private Loto1 loto;
	
	public void actionPerformed(ActionEvent e)
	{
	   this.loto.majNbC();
	}
	//constructeur:
	public AL_jtf (Loto1 l)
	{
	  this.loto=l;
	}
}

class AL_Btn implements ActionListener
{
	private Loto1 loto;
	
	public void actionPerformed(ActionEvent e)
	{
		//On determine quel boutton a ete clique
		JButton btn_clique = (JButton) e.getSource();
		String btn_nom = btn_clique.getText();
		
		if( btn_nom.equals("Valider") )
		{
			this.loto.valider();
		}
		else if( btn_nom.equals("Effacer") )
		{
			this.loto.effacer();
		}
	}
	//constructeur:
	public AL_Btn (Loto1 l)
	{
	  this.loto=l;
	}
}