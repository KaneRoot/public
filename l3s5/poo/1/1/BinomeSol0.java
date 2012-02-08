public class BinomeSol0 extends Binome
{
	public BinomeSol0(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	@Override
	public void CalculeRacines()
	{
		System.out.println("Pas de racines possibles (delta < 0)");
	}
	@Override
	public int NbRacines()
	{
		return 0;
	}
	@Override
	public double ValeurRacine(int i)
	{
		System.out.println("Calcul ValeurRacine : delta < 0, pas de racines!");
		return 0.0;
	}
}
