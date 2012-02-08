public class Saumon extends Poisson
{
	public Saumon(String nom)
	{
		super(nom);
	}
	public Saumon()
	{
		this("");
	}
	
	@Override
	public String GetPresentation()
	{
		return super.GetPresentation() + "Je suis un saumon. ";
	}
}
