// Première classe qui hérite de Binome.
public class BinomeSol0 extends Binome
{
	// constructeur
	public BinomeSol0(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	// Les méthodes redéfinies
	@Override
	public void CalculeRacines()
	{
		System.out.println("Pas de racines possibles (delta < 0)");
	}
	@Override
	public int NbRacines()
	{
		return 0; // Nous n'aurons jamais de racine.
	}
	@Override
	public double ValeurRacine(int i)
	{
		System.out.println("Calcul ValeurRacine : delta < 0, pas de racines!");
		return 0.0; // Valeur renvoyée par défaut. Nous pourrions éventuellement lancer une exception.
	}
}
