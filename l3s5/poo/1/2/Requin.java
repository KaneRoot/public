public class Requin extends Poisson
{
	public Requin(String nom)
	{
		super(nom);
	}
	public Requin()
	{
		this("");
	}
	
	@Override
	public String GetPresentation()
	{
		return super.GetPresentation() + "Je suis un requin. ";
	}
}
