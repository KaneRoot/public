public class Poisson extends Animal
{
	public Poisson(String nom)
	{
		super(nom);
	}
	public Poisson()
	{
		this("");
	}
	@Override
	public String GetPresentation()
	{
		return + super.GetPresentation() + "Je suis un poisson. ";
	}
}
