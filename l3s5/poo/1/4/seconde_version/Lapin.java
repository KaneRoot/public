public class Lapin
{
	public boolean vivant = true;

	public static int NB_LAPINS = 0;

	private Lapin()
	{
	}

	// maintenant qu'un Lapin peut être null, on passe par des méthodes statiques, c'est plus prudent
	private String getEtat()
	{
		if(this.vivant)
			return "vivant";
		return "mort";
	}
	private void casserole()
	{
		if(this.vivant)
		{
			Lapin.NB_LAPINS--;
			this.vivant = false;
		}
	}
	public static void passeALaCasserole(Lapin l)
	{
		if(l != null)
			l.casserole();
	}
	public static Lapin creationLapin()
	{
		if(Lapin.NB_LAPINS >= 50)
			return null;

		Lapin.NB_LAPINS++;
		return new Lapin();

	}
	public static String getEtatLapin(Lapin l)
	{
		if(l == null) 
			return "non existant";

		return l.getEtat();
	}
}
