public class UsineABinome
{
	static Binome CreeBinome(double a, double b, double c)
	{
		double delta = b*b - 4.0 * a * c;
		if(delta < 0.0)			return new BinomeSol0(a,b,c,delta);
		else if(delta > 0.0)	return new BinomeSol2(a,b,c,delta);
		else					return new BinomeSol1(a,b,c,delta);
	}
	public static void main(String args[])
	{
		System.out.println("Début du programme !");
	}
}
