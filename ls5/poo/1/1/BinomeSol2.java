// Dernière classe qui hérite de Binome.
public class BinomeSol2 extends Binome
{
	// Cette fois-ci, nous aurons toujours 2 racines.
	public double[] racines = new double[2];

	// Le constructeur n'a toujours pas changé.
	public BinomeSol2(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	// Les méthodes redéfinies
	@Override
	public void CalculeRacines()
	{
		// Le calcul a légèrement changé.
		this.racines[0] = - (super.getB() + Math.sqrt(super.getDis())) / (2*super.getA());
		this.racines[1] = - (super.getB() - Math.sqrt(super.getDis())) / (2*super.getA());
		System.out.println("Calcul des 2 racines possibles (delta > 0)");
	}
	@Override
	public int NbRacines()
	{
		return 2; // Renverra toujours la même valeur.
	}
	@Override
	public double ValeurRacine(int i)
	{
		System.out.println("Valeur Racine "+ i%2);
		return this.racines[((i%2)+2)%2]; // Évite des erreurs au niveau de la mémoire si i > 1 ou < 0.
	}
}
