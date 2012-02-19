// La classe qui contient la méthode main.
public class Tests
{
	// Les tests pourraient bien sûr être plus poussés.
	public static void main(String args[])
	{
		System.out.println("Début du programme !");
		System.out.println(" \033[31m 2x2 + 4x + 2 \033[00m : ");
		Binome a = UsineABinome.CreeBinome(2.0,4.0,2.0);
		a.CalculeRacines();
		for(int i = 0 ; i < a.NbRacines() ; i++)
			System.out.println("Racine " +i+ " : " + a.ValeurRacine(i));

		System.out.println("\n \033[31m 2x2 + 3x + 2 \033[00m : ");
		Binome b = UsineABinome.CreeBinome(2.0,3.0,2.0);
		b.CalculeRacines();
		for(int i = 0 ; i < b.NbRacines() ; i++)
			System.out.println("Racine " +i+ " : " + b.ValeurRacine(i));

		System.out.println("\n \033[31m 2x2 + 5x + 2 \033[00m : ");
		Binome c = UsineABinome.CreeBinome(2.0,5.0,2.0);
		c.CalculeRacines();
		for(int i = 0 ; i < c.NbRacines() ; i++)
			System.out.println("Racine " +i+ " : " + c.ValeurRacine(i));
	}
}
