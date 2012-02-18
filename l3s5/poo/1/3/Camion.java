public class Camion extends Vehicule
{
	private int nbreEssieu;
	private double poidsTotal;

	private static final int _NB_ESSIEUX = 4;
	private static final double _POIDS = 12.3;

	public Camion(int nbEssieux, double poids)
	{
		this.nbreEssieu = nbEssieux;
		this.poidsTotal = poids;
	}
	public Camion() // constructeur par défaut
	{
		this(_NB_ESSIEUX, _POIDS); // on utilise les valeurs par défaut
	}

	// Ensemble de getter classiques
	public int getNbreEssieu()
	{
		return this.nbreEssieu;
	}
	public double getPoidsTotal()
	{
		return this.poidsTotal;
	}

	// implantation de la méthode getDescription
	public String getDescription()
	{
		return "Je suis un Camion avec " + this.getNbreEssieu() + " essieux et un poids de " + this.getPoidsTotal() + " tonnes";
	}
}
