public class Lapin
{
	public boolean vivant = true;

	public static int NB_LAPINS = 0;

	private Lapin()
	{
	}
	public static Lapin creationLapin()
	{
		if(Lapin.NB_LAPINS >= 50)
			return null;

		Lapin.NB_LAPINS++;
		return new Lapin();

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
