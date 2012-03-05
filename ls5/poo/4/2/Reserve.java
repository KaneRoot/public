public class Reserve
{
	private int nbressources = 10, nbmax = 50;
	public synchronized void prendre(int nb)
	{
		while(true)
		{
			if((nbressources - nb) < 0)
			{
				try
				{
					wait();
				}
				catch(InterruptedException e)
				{
					System.out.println("Exception prendre : " + e.getMessage());
				}
			}
			else
				break;
		}
		System.out.print("Prendre " + nb + " résultat : ");
		nbressources -= nb;
		System.out.println(nbressources);
		try
		{
			notifyAll();
		}
		catch(IllegalMonitorStateException e)
		{
			System.out.println("Exception notify : " + e.getMessage());
		}
	}
	public synchronized void mettre(int nb)
	{
		while(true)
		{
			if((nbressources + nb) > nbmax)
			{
				try
				{
					wait();
				}
				catch(InterruptedException e)
				{
					System.out.println("Exception mettre : " + e.getMessage());
				}
			}
			else
				break;
		}
		System.out.print("Mettre " + nb + " résultat : ");
		nbressources += nb;
		System.out.println(nbressources);
		try
		{
			notifyAll();
		}
		catch(IllegalMonitorStateException e)
		{
			System.out.println("Exception notify : " + e.getMessage());
		}
	}
}
