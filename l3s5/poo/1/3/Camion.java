public class Camion extends Vehicule
{
	private int nbreEssieu;
	private double poidsTotal;

	public Camion(int nbEssieux, double poids)
	{
		this.nbreEssieu = nbEssieux;
		this.poidsTotal = poids;
	}
	public int getNbreEssieu()
	{
		return this.nbreEssieu;
	}
	public double getPoidsTotal()
	{
		return this.poidsTotal;
	}
}
