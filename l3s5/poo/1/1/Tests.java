// La classe qui contient la méthode main.
public class Tests
{
	// Les tests pourraient bien sûr être plus poussés.
	public static void main(String args[])
	{
		System.out.println("Début du programme !");
		System.out.println("2x2 + 4x + 2 : ");
		Binome a = UsineABinome.CreeBinome(2.0,4.0,2.0);
		a.CalculeRacines();
		for(int i = 0 ; i < a.NbRacines() ; i++)
			System.out.println("Racine " +i+ " " + a.ValeurRacine(i));
	}
}
