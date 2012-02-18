import java.lang.String.*;
public class Animal
{
	// Chaque animal a un nom. 
	// Parfois il est vide mais ce n'est pas le caractère propre d'un animal en particulier.
	// nom = "" si vide.
	public String nom;

	// Les 2 constructeurs sont redéfinis dans chaque classe.
	public Animal(String nom)
	{
		this.nom = nom;
	}
	// Si on ne souhaite pas que l'animal ait un nom.
	public Animal()
	{
		this(""); 
	}
	// Première définition de GetPresentation.
	public String GetPresentation()
	{
		if(this.nom.equals("")) // si nom = "" alors l'animal n'a pas de nom.
			return "Je suis un animal sans nom. ";
		else
			return "Je suis un animal de nom " + this.nom + ". ";
	}
}
