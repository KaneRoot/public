public class Reserve
{
	private int nbressources = 10, nbmax = 50;
	public synchronized void prendre(int nb)
	{
		while((nbressources - nb) < 0)
		{
			try { wait(); }
			catch(InterruptedException e) { System.out.println("Exception prendre : " + e.getMessage()); }
		}
		nbressources -= nb;
		System.out.println("Prendre " + nb + " résultat : " + nbressources);

		try { notifyAll(); }
		catch(IllegalMonitorStateException e) { System.out.println("Exception notify : " + e.getMessage()); }
	}
	public synchronized void mettre(int nb)
	{
		while((nbressources + nb) > nbmax)
		{
			try { wait(); } 
			catch(InterruptedException e) { System.out.println("Exception mettre : " + e.getMessage()); }
		}

		nbressources += nb;
		System.out.println("Mettre " + nb + " résultat : " + nbressources);

		try { notifyAll(); } 
		catch(IllegalMonitorStateException e) { System.out.println("Exception notify : " + e.getMessage()); }
	}
}
