import java.util.Scanner;
import java.lang.String;
import java.util.ArrayList;
import java.io.File;
public class EssaisPersonnes
{
	public static void main(String[] args)
	{
		ArrayList<Personne> Liste;
		Liste = lirePersonne(args[0]);
		
	}
	public static ArrayList<Personne> extraire(ArrayList<Personne> origineList, String begin)
	{
		ArrayList<Personne> personnestries = new ArrayList<Personne>();
		for(Personne personne : origineList)
		{
			if(personne.getNom().startsWith(begin))
			{
				personnestries.add(personne);
			}
		}
		return personnestries;
	}
	public static ArrayList<Personne> lirePersonne(String nomFichier)
	{
		File fichier = new File(nomFichier);
		ArrayList<Personne> liste = new ArrayList<Personne>();
			try
			{
				Scanner sc = new Scanner(fichier);
				while(sc.hasNextLine())
				{
					liste.add(EssaisPersonnes.toPersonne(sc.nextLine()));
				}
				sc.close();
				return liste;
			}
			catch(java.io.FileNotFoundException nf) 
			{
				System.out.println(nf.getMessage());
			}
		return liste;
	}

	public static Personne toPersonne(String ligne)
	{
		String[] perso = ligne.split(" ");
		Personne bla;
		char deb = perso[0].charAt(0);
		
		switch(deb)
		{
			case '1' :
				bla = new Etudiant(perso[1],perso[2],Personne.toDate(perso[3]),Integer.parseInt(perso[4]),Integer.parseInt(perso[5]));
			break;
			case '2' : 
				bla = new Enseignant(perso[1],perso[2],Personne.toDate(perso[3]),Integer.parseInt(perso[4]),Integer.parseInt(perso[5]));
			break;
			default:
				bla = new Utilisateur(perso[0],perso[1],Personne.toDate(perso[2]));
			break;
		}
		return bla;
	}
}
