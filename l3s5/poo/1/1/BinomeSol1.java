// Seconde classe qui hérite de Binome.
public class BinomeSol1 extends Binome
{
	// Ici nous avons une variable qui contiendra la "racine" unique
	// Cette variable était bien entendu inutile dans Binome et BinomeSol0
	// Et ne sera pas adaptée à BinomeSol2 = inutile également
	public double racine;

	// constructeur
	public BinomeSol1(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	// Les méthodes redéfinies
	@Override
	public void CalculeRacines()
	{
		// On récupère les valeurs qui nous seront utiles pour les calculs.
		// Ceci grâce aux getters définis dans la classe mère.
		this.racine = - super.getB() / (2*super.getA());
		System.out.println("Calcul de la racine possible (delta == 0)");
	}
	@Override
	public int NbRacines()
	{
		return 1; // Nous n'aurons qu'une seule racine dans tous les cas dans cette classe.
	}
	@Override
	public double ValeurRacine(int i) // Le "i" est ignoré.
	{
		System.out.println("Calcul ValeurRacine : delta == 0, qu'une racine!");
		return this.racine;
	}
}
