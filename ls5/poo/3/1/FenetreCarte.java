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
}


class Carte
{
	/*
	 * Créée une FenetreCarte et affiche la topologie de la carte
	 *
	 **/
	public void Afficher()
	{
	}
}


class PanneauCarte extends JPanel
{
	public Carte c;
	public PanneauCarte(Carte c)
	{
		this.c = c;
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
