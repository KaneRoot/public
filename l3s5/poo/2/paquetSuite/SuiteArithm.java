package paquetSuite;
import paquetException.*;

public class SuiteArithm extends Suite
{
	public SuiteArithm(int premier, int pas)
	{
		super(premier, pas);
	}

	public int valeurAuRangN(int n) throws paquetException.SuiteException
	{
		if(n < 0) throw new paquetException.SuiteException("Suite arithm n < 0 ");
		return this.premier + n * this.pas;
	}
	public int sommeAuRangN(int n) throws SuiteException
	{
		if(n < 0) throw new SuiteException("Suite arithm n < 0 ");
		return n * (this.premier + this.valeurAuRangN(n-1))/2;
	}
}
