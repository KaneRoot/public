package util;
import java.io.*;
import modele.*;
import modele.elements.*;
import modele.elements.E_fixe;
import modele.elements.E_item;
import modele.elements.E_lethal;

/**
 *
 * Charge la carte qui se trouve dans le répertoire maps/ .
 *
 */

public class ChargementMap
{
	protected String source;
	private Map m = null;

	/**
	 * Le constructeur
	 *
	 * @param source le répertoire qui contient les cartes
	 *
	 */
	public ChargementMap(String source)
	{
		this.source = source;
	}

	/**
	 * Pour tester une ligne du fichier de configuration
	 *
	 */
	private int testLigne(String ligne)
	{
		String[] options = ligne.split(":");

		if(0 == options[0].compareTo("nom"))
		{
			this.m.setNom(options[1]);
		}
		else if(0 == options[0].compareTo("taille"))
		{
			try 
			{ 
				this.m.setW(getInt(options[1]));
				this.m.setH(getInt(options[2]));
			}
			catch(Exception e) { return -1; }
		}
		else if(0 == options[0].compareTo("arrivee"))
		{
			try
			{
				this.m.setArrivee(getInt(options[1]));
			}
			catch(Exception e) { return -1; }
		}
		else if(0 == options[0].compareTo("sol"))
		{
			try
			{
				this.m.addPoint(new Point2d(getInt(options[1]), getInt(options[2])));
			}
			catch(Exception e) { return -1; }
		}

		else if(0 == options[0].compareTo("perso"))
		{
			try
			{
				Class c = Class.forName("modele.elements." + options[1]);
				E_perso p = (E_perso) c.newInstance();
				p.setPosition(getInt(options[2]), getInt(options[3]));
				p.setSize(getInt(options[4]));
				p.setOptions(options);
				this.m.setPerso(p);
			}
			catch(Exception e) { System.out.println("Erreur création du perso"); return -1; }

		}
		else
		{
			try
			{
				Class c = Class.forName("modele.elements." + options[0]);
				Element e = (Element) c.newInstance();
				e.setPosition(getInt(options[1]), getInt(options[2]));
				e.setSize(getInt(options[3]));
				e.setOptions(options);
				this.m.addElem(e);
			}
			catch(Exception e) 
			{
				e.printStackTrace(); 
				System.out.println("Option inconnue : " + options[0]);
				return -1; 
			}
		}
		return 0;
	}

	/**
	 * Lecture du fichier de configuration.
	 *
	 */
	private void lecture() 
	{ 
		this.m = new Map();
		try 
		{
			String ligne ;
			BufferedReader fichier = new BufferedReader(new FileReader(this.source));

			while ((ligne = fichier.readLine()) != null)
			{
				// Suppression des commentaires dans la ligne
				ligne = ligne.replaceAll("#.*$", "");

				// On ne fait rien avec les lignes vides
				if(ligne.length() > 1)
					if( -1 == testLigne(ligne))
						System.out.println("Il y a eu une erreur à la ligne : " + ligne);
			}

			if( this.m.getNom() == null)
				this.m.setNom(this.source);

			this.m.getPerso().setPosition(this.m.getPerso().getPosition().getX(), 
					this.m.getYSol(m.getPerso().getPosition().getX()));

			fichier.close();
		} 
		catch (Exception e) { e.printStackTrace(); }     
	}

	/**
	 * @return une instance de Map correspondant au fichier de configuration
	 *
	 */
	public Map getMap()
	{
		if(this.m == null)
			this.lecture();
		return m;
	}

	/**
	 * Fonction de conversion d'un string en entier.
	 *
	 * Utile uniquement dans cette classe.
	 *
	 * @param s : la chaîne de caractères.
	 *
	 * @return entier correspondant à s.
	 */

	private int getInt(String s)
	{
		int i;

		try { i = Integer.parseInt(s); }
		catch(NumberFormatException e) { return -1; }
		return i;
	}
}
