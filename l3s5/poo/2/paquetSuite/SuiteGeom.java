package paquetSuite;
import java.lang.Math.*;

public class SuiteGeom extends Suite
{
	public SuiteGeom(int premier, int pas)
	{
		super(premier, pas);
	}

	public int valeurAuRangN(int n)
	{
		return this.premier * (int) java.lang.Math.pow((double) this.pas, (double) n);
	}
	public int sommeAuRangN(int n)
	{
		if(this.pas == 1) return n*this.premier;
		return this.premier * (1 - (int) Math.pow((double) this.pas, (double) n))/(1 - this.pas);
	}
}
