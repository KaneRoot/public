public class BinomeSol1 extends Binome
{
	public double racine;
	public BinomeSol1(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	@Override
	public void CalculeRacines()
	{
		this.racine = - super.getB() / (2*super.getA());
		System.out.println("Calcul de la racine possible (delta == 0)");
	}
	@Override
	public int NbRacines()
	{
		return 1;
	}
	@Override
	public double ValeurRacine(int i)
	{
		System.out.println("Calcul ValeurRacine : delta == 0, qu'une racine!");
		return this.racine;
	}
}
