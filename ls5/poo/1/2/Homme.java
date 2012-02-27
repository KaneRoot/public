public class Homme extends Mammifere
{
	public Homme(String nom)
	{
		super(nom);
	}
	public Homme()
	{
		this("");
	}
	
	@Override
	public String GetPresentation()
	{
		return super.GetPresentation() + "Je suis un homme. ";
	}
}
