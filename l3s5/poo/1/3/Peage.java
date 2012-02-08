public class Peage
{
	private int nbreVehicule, totalCaisse;
	private double prixEssieux, prixTonne;
	private static PRIX_VOITURE = 4;
	public Peage(double prixE, double prixT)
	{
		this.prixEssieux = prixE;
		this.prixTonne = prixT;
	}
	public Peage()
	{
		this(7.0,15.0);
	}
	public void passage(Vehicule v)
	{
		this.nbreVehicule++;
		if(v instanceof Camion)
		{
			double poids = ((Camion)v).getPoidsTotal();
			int poidsFinal = (int) poids;
			if(poids%1 != 0) poidsFinal++;
			this.totalCaisse += this.prixEssieux * ((Camion)v).getNbreEssieu() + this.prixTonne * poidsFinal;
		}
		else
			this.totalCaisse += PRIX_VOITURE;
	}

	public int getTotalCaisse()
	{
		return this.totalCaisse;
	}
}
