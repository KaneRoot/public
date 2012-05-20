package vue.menu;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.Font;
import javax.swing.JApplet;
import javax.swing.JLabel;

import modele.listener.*;
import controleur.ControleurMenu;

/**
 * Classe du Menu.
 *
 * Affiche l'ensemble des boutons du menu principal.
 *
 */

public class Menu extends VueMenu 
{
	/** Le bouton pour lancer une nouvelle partie. */
	public JButton jb_partie = new JButton("Nouvelle partie");

	/** Le bouton pour recommencer une partie. */
	public JButton jb_recommencer = new JButton("Continuer");
	
	/** Le bouton pour aller au menu du choix de la carte. */
	public JButton jb_map = new JButton("Choix de la carte !");

	/** Ce qu'on affiche en haut du menu. */
	public JLabel jl_titre = new JLabel("");

	/**
	 * @param c : controleur du menu.
	 *
	 */

	public Menu(ControleurMenu c)
	{
		super(c);

		jb_partie.addActionListener(new JBStartGameListener(this.getControleur(), this));
		jb_recommencer.addActionListener(new JBResumeListener(this.getControleur(), this));
		jb_map.addActionListener(new JBMapChoiceListener(this.getControleur(), this));

		this.setLayout(new BorderLayout());
		this.add(jl_titre,BorderLayout.NORTH);
		this.add(jb_partie,BorderLayout.CENTER);
		this.add(jb_map, BorderLayout.EAST);
		this.add(jb_recommencer,BorderLayout.SOUTH);
		this.setMessage("CE JEU EST VRAIMENT TRÈS BIEN.");

		this.setSize(1000,500);
		this.repaint();

		this.getControleur().jf_jeu.pack();
		/*
		*/
	}
	/**
	 * Change le message affiché en haut du menu.
	 *
	 * @param s : la chaîne de caractères à afficher en remplacement.
	 *
	 */

	public void setMessage(String s)
	{
		Font font = new Font("Courier", Font.BOLD,20);
		this.jl_titre.setText(s);
		this.jl_titre.setFont(font);
		this.getControleur().jf_jeu.repaint();
	}
	/*
	public void paint(Graphics g)
	{
		this.setSize(1000,500);
		super.paint(g);
		this.setSize(1000,500);
	}
	*/
}
