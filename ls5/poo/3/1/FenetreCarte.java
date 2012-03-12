import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FenetreCarte extends JFrame
{
	/*
	 * Créée un PanneauCarte et l'ajoute au contenu de la fenêtre
	 *
	 **/
	public void Afficher(Carte c)
	{
	}
	public FenetreCarte()
	{
		super();
		build();
	}
	private void build()
	{
		setTitle("Premier Exercice");
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(buildContentPane());
		setVisible(true);
	}
	private JPanel buildContentPane()
	{
		Carte[] c = new Carte[6*7];
		for(int i = 0 ; i < (6*7) ; i++)
			c[i] = new Carte("" + i);

		JPanel panel = new PanneauCarte(c);
		return panel;
	}
	public static void main(String[] args)
	{
		SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				FenetreCarte f = new FenetreCarte();
			}
		});
	}
}

class Carte extends JButton
{
	/*
	 * Créée une FenetreCarte et affiche la topologie de la carte
	 *
	 **/
	public Carte(String s)
	{
		super(s);
		this.setSize(50,50);
	}
	public void Afficher()
	{
	}
}


class PanneauCarte extends JPanel
{
	public Carte[] c;
	public PanneauCarte(Carte[] c)
	{
		this.c = c;
		this.setLayout(new GridLayout(6,7));
		this.setBackground(Color.black);
		for(int i = 0 ; i < (6*7) ; i++)
			this.add(c[i]);
	}
	/*
	 * Redéfinition de paint pour dessiner la carte
	 *
	 **/
	@Override
	public void paint(Graphics g)
	{
	}
}
