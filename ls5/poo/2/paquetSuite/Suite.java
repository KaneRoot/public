package paquetSuite;

import paquetException.*;

public abstract class Suite
{
	// premier = u0 , pas = raison
	public int premier, pas;
	public Suite(int premier, int pas)
	{
		this.premier = premier;
		this.pas = pas;
	}
	public abstract int valeurAuRangN(int n) throws SuiteException;
	public abstract int sommeAuRangN(int n) throws SuiteException;

}
