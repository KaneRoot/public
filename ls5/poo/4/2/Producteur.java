public class Producteur extends Thread
{
	Reserve r;
	public Producteur(Reserve r)
	{
		super();
		this.r = r;
	}
	@Override
	public void run()
	{
		int i = 0;
		while(i < 1000)
		{
			r.mettre(5);
			try
			{
				Thread.sleep((int)Math.random() * 1000);
			}
			catch(Exception e)
			{
				System.out.println("Exception producteur : " + e.getMessage());
			}
			i++;
		}
	}
}
