public class TestLapins
{
	public static void main(String[] args)
	{
		int i;
		Lapin[] l = new Lapin[65];

		System.out.println("Création de 60 lapins");
		for(i = 0 ; i < 60 ; i++)
			l[i] = new Lapin();
		for(i = 0 ; i < 60 ; i++)
			System.out.print("l["+i+"] = " + l[i].getEtat() + " ; ");

		System.out.println("\n\n \033[36m On passe à la casserole les 10 premiers\033[00m puis on en crée 15 de plus");
		for(i = 0 ; i < 10 ; i++)
			l[i].passeALaCasserole();
		for(i = 0 ; i < 15 ; i++)
			l[i+50] = new Lapin();

		System.out.println("On affiche tous les lapins \n");

		for(i = 0 ; i < 65 ; i++)
			System.out.print("l["+i+"] = " + l[i].getEtat() + " ; ");

		System.out.println("");
	}
	
}
