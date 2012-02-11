public class Global
{
	public static void main(String[] args)
	{
		int i; // Incrément utile pour les passages au péage de X véhicules

		System.out.println("Début du programme");
		System.out.println("Création de 2 péages");

		Peage[] P = new Peage[2];
		P[0] = new Peage(1,2.5);
		P[1] = new Peage(5,1.5);

		System.out.println("Description des deux péages : \n");
		System.out.println("	\033[36mPEAGE 1\033[00m\n" + P[0].getDescription());
		System.out.println("	\033[36mPEAGE 2 \033[00m\n" + P[1].getDescription());
		System.out.println("\n\nPEAGE 1");

		Vehicule[] V = new Vehicule[6];
		for(i = 0 ; i < 2 ; i++)
			V[i] = new Camion(i, i + 10.3);
		V[i++] = new Voiture();
		V[i++] = new VoitureChef();
		V[i++] = new Moto();
		V[i] = new Voiture();


		Global.faire_passage(P[0], V[0]);
		Global.afficher_total(P[0]);

		System.out.println("\n\nPEAGE 2");
		for(i = 0 ; i < 6 ; i++)
		{
			Global.faire_passage(P[1], V[i]);
			Global.afficher_total(P[1]);
		}
		

	}
	public static void afficher_total(Peage p)
	{
		System.out.println("\033[31m---------------\033[00m");
		System.out.println("EN CAISSE : " + p.getTotalCaisse());
		System.out.println("\033[31m---------------\033[00m");
	}
	public static void faire_passage(Peage p, Vehicule v)
	{
		System.out.println("	Passage véhicule : " + v.getDescription());
		p.passage(v);
	}
}
