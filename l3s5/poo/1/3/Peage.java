public class Peage
{
	private int nbreVehicule, totalCaisse;
	private double prixEssieux, prixTonne;
	private static int PRIX_VOITURE = 4;

	private static double PRIX_ESSIEUX = 7.0;
	private static double PRIX_TONNE = 15.0;

	public Peage(double prixE, double prixT)
	{
		this.prixEssieux = prixE;
		this.prixTonne = prixT;
	}
	public Peage()
	{
		this(PRIX_ESSIEUX, PRIX_TONNE);
	}
	public void passage(Vehicule v)
	{
		this.nbreVehicule++;
		if(v instanceof Camion)
		{
			double poids = ((Camion)v).getPoidsTotal();
			int poidsFinal = (int) poids;
			if( poids % 1 != 0.0) poidsFinal++;
			this.totalCaisse += this.prixEssieux * ((Camion)v).getNbreEssieu() + this.prixTonne * poidsFinal;
		}
		else
			this.totalCaisse += PRIX_VOITURE;
	}

	public int getTotalCaisse()
	{
		return this.totalCaisse;
	}
	public int getTotalVehicules()
	{
		return this.nbreVehicule;
	}
	public String getDescription()
	{
		return	"Ce peage fait payer :\n" +
				"	" + this.prixEssieux + " € / essieu et " + this.prixTonne + " € / tonne aux camions \n" +
				"	" + this.PRIX_VOITURE + " € / voiture";
	}
}
