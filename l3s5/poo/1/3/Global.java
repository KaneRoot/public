public class Global
{
	public static void main(String[] args)
	{
		System.out.println("Début du programme");

		System.out.println("Création de 2 péages");

		Peage[] P = new Peage[2];
		P[0] = new Peage();
		P[1] = new Peage(5,15.3);

		System.out.println("Description des deux péages : \n");
		System.out.println("	\033[36mPEAGE 1\033[00m\n" + P[0].getDescription());
		System.out.println("	\033[36mPEAGE 2 \033[00m\n" + P[1].getDescription());
		Vehicule[] V = new Vehicule[5];
		for(int i = 0 ; i < 5 ; i++)
			V[i] = new Camion(i+3,i+5.4);

		Global.faire_passage(P[0], V[0]);
		Global.afficher_total(P[0]);
		
/*
		for(int k = 0 ; k < 10 ; k++)
			Global.faire_passage(P[0], V[k%5]);

		
		Global.afficher_total(P[0]);
*/
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
