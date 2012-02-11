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
	public Camion()
	{
		this(_NB_ESSIEUX, _POIDS);
	}
	public int getNbreEssieu()
	{
		return this.nbreEssieu;
	}
	public double getPoidsTotal()
	{
		return this.poidsTotal;
	}
	public String getDescription()
	{
		return "Je suis un Camion avec " + this.getNbreEssieu() + " essieux et un poids de " + this.getPoidsTotal() + " tonnes";
	}
}
