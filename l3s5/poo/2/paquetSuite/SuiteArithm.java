package paquetSuite;

public class SuiteArithm extends Suite
{
	public SuiteArithm(int premier, int pas)
	{
		super(premier, pas);
	}

	public int valeurAuRangN(int n)
	{
		return this.premier + n * this.pas;
	}
	public int sommeAuRangN(int n)
	{
		return n * (this.premier + this.valeurAuRangN(n-1))/2;
	}
}
