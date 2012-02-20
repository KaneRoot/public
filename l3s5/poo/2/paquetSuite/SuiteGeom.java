package paquetSuite;
import java.lang.Math.*;
import paquetException.*;

public class SuiteGeom extends Suite
{
	public SuiteGeom(int premier, int pas)
	{
		super(premier, pas);
	}

	public int valeurAuRangN(int n) throws SuiteException
	{
		if(n < 0) throw new SuiteException("Suite Geom n < 0 ");
		return this.premier * (int) java.lang.Math.pow((double) this.pas, (double) n);
	}
	public int sommeAuRangN(int n) throws SuiteException
	{
		if(n < 0) throw new SuiteException("Suite Geom n < 0 ");
		if(this.pas == 1) return n*this.premier;
		return this.premier * (1 - (int) Math.pow((double) this.pas, (double) n))/(1 - this.pas);
	}
}
