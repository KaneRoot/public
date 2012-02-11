public class Peage
{
	private int nbreVehicule, nbMoto, nbVoiture, nbCamion;
	private double prixEssieux, prixTonne, totalCaisse;
	private double prix_voiture = 4.0;
	private double prix_moto = 5.0;

	// Valeurs par défaut
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
			this.nbCamion++;
			int poidsFinal = (int) ((Camion)v).getPoidsTotal();
			if( ((Camion)v).getPoidsTotal() % 1 != 0.0) poidsFinal++;
			this.totalCaisse += (this.prixEssieux * ((Camion)v).getNbreEssieu()) + 
				(this.prixTonne * poidsFinal);
		}
		else if (v instanceof Moto)
		{
			this.nbMoto++;
			this.totalCaisse += prix_moto;
		}
		else if ( ! (v instanceof VoitureChef))
		{
			this.nbVoiture++;
			this.totalCaisse += prix_voiture;
		}
		else
			this.nbVoiture++;
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
				"	" + this.prixEssieux + " € / essieu et " + 
					this.prixTonne + " € / tonne aux camions \n" +
				"	" + this.prix_voiture + " € / voiture" + 
				"	" + this.prix_moto + " € / moto";
	}
	public String getDetailsVehicules()
	{
		return "Nb voitures : " + this.nbVoiture + " | Nb moto : " + this.nbMoto +
			" | Nb camions : " + this.nbCamion;
	}
}
