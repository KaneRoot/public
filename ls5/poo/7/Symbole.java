public class Symbole
{
	public String chaine;
	public boolean estOp;
	public int nb;
	
	public Symbole(String s) throws Exception
	{
		this.chaine = s;
		try
		{
			this.nb = Integer.parseInt(this.chaine);
			this.estOp = false;
		}
		catch(NumberFormatException e)
		{
			if(		chaine.compareTo("+") == 0 || 
					chaine.compareTo("-") == 0 ||
					chaine.compareTo("/") == 0 ||
					chaine.compareTo("*") == 0)
			{
				this.estOp = true;
			}
			else
			{
				throw new Exception();
			}
		}
	}
	
	public boolean estNombre()
	{
		return ! estOp;
	}
	public boolean estOperation()
	{
		return estOp;
	}
	public int getNombre()
	{
		return this.nb;
	}
	public char getOperation()
	{
		return this.chaine.charAt(0);
	}
}
