public class Symbole
{
	String chaine;
	public Symbole(String s)
	{
		this.chaine = s;
	}
	public boolean estNombre()
	{
		try
		{
			Integer.parseInt(this.chaine);
		}
		catch(NumberFormatException e)
		{
			System.out.prinln("Exception : " + chaine + " n'est pas un nombre");
			return false;
		}
		return true;
	}
	public boolean estOperation()
	{
		if(! estNombre())
		{
		}
	}
}
