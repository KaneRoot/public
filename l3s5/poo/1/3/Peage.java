public class Peage
{
	private int nbreVehicule;
	private double prixEssieux, prixTonne, totalCaisse;
	private int PRIX_VOITURE = 4;
	private int PRIX_MOTO = 5;

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
			int poidsFinal = (int) ((Camion)v).getPoidsTotal();
			if( ((Camion)v).getPoidsTotal() % 1 != 0.0) poidsFinal++;
			System.out.println("POIDS : " + poidsFinal);
			this.totalCaisse += this.prixEssieux * ((Camion)v).getNbreEssieu() + this.prixTonne * poidsFinal;
		}
		else if (v instanceof Moto)
			this.totalCaisse += PRIX_MOTO;
		else if ( ! (v instanceof VoitureChef))
			this.totalCaisse += PRIX_VOITURE;
	}

	public double getTotalCaisse()
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
				"	" + this.PRIX_VOITURE + " € / voiture" + 
				"	" + this.PRIX_MOTO + " € / moto";
	}
}
