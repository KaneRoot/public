package test;

import java.io.*;
import java.util.ArrayList;

import modele.Map;
import util.ChargementMap;
import util.ListeMaps;

/**
 * @deprecated servait à tester le chargement des cartes.
 *
 * @see util.ChargementMap
 */

public class TestMaps
{
	/**
	 * Lancement du programme de test.
	 *
	 */

	public static void main(String[] args)
	{
		ListeMaps lesmaps = new ListeMaps("./maps");
		ArrayList<Map> ml = lesmaps.getListe();
		for(Map m : ml)
			System.out.println("Le nom de la map : " + m.getNom());
	}
}
