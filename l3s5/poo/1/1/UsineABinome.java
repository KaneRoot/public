public class UsineABinome
{
	// Crée des instances de sous-classes de la classe Binome.
	static Binome CreeBinome(double a, double b, double c)
	{
		double delta = b*b - 4.0 * a * c;
		if(delta < 0.0)			return new BinomeSol0(a,b,c,delta);
		else if(delta > 0.0)	return new BinomeSol2(a,b,c,delta);
		else					return new BinomeSol1(a,b,c,delta);
	}
}
