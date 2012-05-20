package util;

import java.io.*;
import java.util.ArrayList;
import util.ChargementMap;
import modele.Map;

public class ListeMaps
{
	private ArrayList<Map> _liste;

	public ListeMaps(String s)
	{
		this._liste = getMaps(s);
	}
	private ArrayList<Map> getMaps(String mapdir)
	{
		return getMaps(new File(mapdir));
	}
	private ArrayList<Map> getMaps(File file)
	{
		ArrayList<Map> liste = new ArrayList<Map>();

		for (File f : file.listFiles())
		{
			if (f.isDirectory())
			{
				liste.addAll(this.getMaps(f));
			}
			else if (! (f.getName().charAt(0) == '.')) // pas besoin des fichiers cachés
			{
				// System.out.println("Fichier : " + f.getName());
				ChargementMap lamap = new ChargementMap(f.getAbsolutePath());
				liste.add(lamap.getMap());
			}
		}
		return liste;
	}
	public ArrayList<Map> getListe()
	{
		return _liste;
	}
}
