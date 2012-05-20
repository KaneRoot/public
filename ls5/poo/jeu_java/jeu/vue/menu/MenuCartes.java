package vue.menu;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;

import modele.Map;
import modele.listener.*;
import controleur.ControleurMenu;
import util.*;

/**
 * Gère l'affichage du menu de sélection de la carte sur laquelle jouer.
 *
 */

public class MenuCartes extends VueMenu
{
	/** La liste des cartes générées. */
	private ArrayList<Map> maliste;

	/** Le répertoire qui contient les cartes. */
	private String rep_cartes;

	/** Le panneau avec les boutons de sélection de carte. */
	private JPanel jp_boutons;

	/** Le bouton de retour. */
	private JButton jb_retour;

	/** Le titre du menu. */
	private JLabel jl_titre = new JLabel("");

	/**
	 * @param c : Controleur du Menu principal.
	 * @param s : Le répertoire cartes.
	 *
	 */
	public MenuCartes(ControleurMenu c, String s)
	{
		super(c);

		this.jb_retour = new JButton("Retour");
		JButton jb; // Variable temporaire

		this.setMessage("Choisissez votre carte !");
		jb_retour.addActionListener(new JBRetourMenuListener(this.getControleur(), this));
		jb_retour.setSize(50,100);

		this.rep_cartes = s;
		this.maliste = new ListeMaps(s).getListe();

		this.setSize((this.maliste.size() / 2) * 500, (this.maliste.size() % 2) * 50);

		this.jp_boutons = new JPanel();

		this.setLayout(new BorderLayout());

		this.jp_boutons.setLayout(new GridLayout(2, 1 + (this.maliste.size() / 2)));
		Font font = new Font("Courier", Font.BOLD,13);
		for(Map m : this.maliste)
		{
			jb = new JButton(m.getNom());
			jb.setFont(font);
			jb.addActionListener(new JBMapListener(this.getControleur(), this, m));
			jb.setSize(50,100);

			this.jp_boutons.add(jb);
		}
		this.jp_boutons.add(jb_retour);

		this.add(jl_titre, BorderLayout.NORTH);
		this.add(jp_boutons, BorderLayout.SOUTH);
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
}
