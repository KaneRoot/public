public class TestLapins
{
	public static void main(String[] args)
	{
		// On ne passe plus que par des méthodes statiques
		int i;
		Lapin[] l = new Lapin[65];

		System.out.println("Création de 60 lapins");
		for(i = 0 ; i < 60 ; i++)
			l[i] = Lapin.creationLapin();
		for(i = 0 ; i < 60 ; i++)
			System.out.print("l["+i+"] = " + Lapin.getEtatLapin(l[i]) + " ; ");

		System.out.println("\n\n \033[36m On passe à la casserole les 10 premiers\033[00m puis on en crée 15 de plus");
		for(i = 0 ; i < 10 ; i++)
			Lapin.passeALaCasserole(l[i]);
		for(i = 0 ; i < 15 ; i++)
			l[i+50] = Lapin.creationLapin();

		System.out.println("On affiche tous les lapins \n");

		for(i = 0 ; i < 65 ; i++)
			System.out.print("l["+i+"] = " + Lapin.getEtatLapin(l[i]) + " ; ");

		System.out.println("");
	}
	
}
