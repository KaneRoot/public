/**
 * @author Karchnu
 * @version 1.0-alpha
 * @since 2012-02-20
 */

package paquetException;

public class SuiteException extends Exception
{
	/**
	 * erreur : chaîne de caractères contenant l'erreur
	 */
	String erreur;

	/**
	 * Constructeur de l'exception
	 *
	 * @param nom : nom de l'erreur
	 */
	public SuiteException(String nom)
	{
		this.erreur = nom;
	}
	/**
	 * retourne le message d'erreur
	 *
	 * @return String_erreur
	 */
	public String getMessage()
	{
		return this.erreur;
	}
}
