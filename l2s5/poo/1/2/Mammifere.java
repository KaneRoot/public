public class Mammifere extends Animal
{
	public Mammifere(String nom)
	{
		super(nom);
	}
	public Mammifere()
	{
		this("");
	}

	@Override
	public String GetPresentation()
	{
		return super.GetPresentation() + "Je suis un mammifère. ";
	}
}
