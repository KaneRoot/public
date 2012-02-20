package paquetException;

public class SuiteException extends Exception
{
	String erreur;
	public SuiteException(String nom)
	{
		this.erreur = nom;
	}
	public String getMessage()
	{
		return this.erreur;
	}
}
