public class Chateau
{
}
// N
class Piece
{
	Personnage p; // Le personnage à l'intérieur
	public Piece()
	{
	}
	public void entrer(Personnage perso)
	{
		this.p = perso;
	}
	public void sortir()
	{
		this.p = null;
	}
}
