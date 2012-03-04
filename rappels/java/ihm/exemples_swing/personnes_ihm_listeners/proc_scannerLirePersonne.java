
	public static ArrayList<Personne> lirePersonne(String nomFichier)
	{
		File fichier = new File(nomFichier);
		ArrayList<Personne> liste = new ArrayList<Personne>();
			try
			{
				Scanner sc = new Scanner(fichier);
				while(sc.hasNextLine())
				{
					ajouter(liste, toPersonne(sc.nextLine()));
				}
				sc.close();
				return liste;
			}
			catch(java.io.FileNotFoundException nf) 
			{
				println(nf);
			}
		
		return liste;
		
	}
	
