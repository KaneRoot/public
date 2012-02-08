public class BinomeSol2 extends Binome
{
	public double[] racines = new double[2];
	public BinomeSol2(double a, double b, double c, double delta)
	{
		super(a,b,c,delta);
	}
	
	@Override
	public void CalculeRacines()
	{
		this.racines[0] = - (super.getB() + Math.sqrt(super.getDis())) / (2*super.getA());
		this.racines[1] = - (super.getB() - Math.sqrt(super.getDis())) / (2*super.getA());
		System.out.println("Calcul des 2 racines possibles (delta > 0)");
	}
	@Override
	public int NbRacines()
	{
		return 2;
	}
	@Override
	public double ValeurRacine(int i)
	{
		System.out.println("Valeur Racine "+ i%2);
		return this.racines[i%2];
	}
}
