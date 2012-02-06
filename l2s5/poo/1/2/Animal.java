public class Animal
{
	public String nom;
	public Animal(String nom)
	{
		this.nom = nom;
	}
	public Animal()
	{
		this("");
	}
	public String GetPresentation()
	{
		if(this.nom.strcmp("") == 0)
			return "Je suis un animal sans nom. ";
		else
			return "Je suis un animal de nom " + this.nom + ". ";
	}
}
