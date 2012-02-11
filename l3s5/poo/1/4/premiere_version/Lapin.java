public class Lapin
{
	public boolean vivant = true;

	public static int NB_LAPINS = 0;

	public Lapin()
	{
		if(Lapin.NB_LAPINS >= 50) // la comparaison pourrait être remplacée par == 
			this.vivant = false;
		else
			Lapin.NB_LAPINS++;
	}
	public void passeALaCasserole()
	{
		if(this.vivant)
		{
			Lapin.NB_LAPINS--;
			this.vivant = false;
		}
	}
	public String getEtat()
	{
		if(this.vivant)
			return "vivant";
		return "mort";
	}
}
