public class Consommateur extends Thread
{
	Reserve r;
	public Consommateur(Reserve r)
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
			r.prendre(5);
			try
			{
				Thread.sleep((int)Math.random() * 5000);
			}
			catch(Exception e)
			{
				System.out.println("Exception consommateur : " + e.getMessage());
			}
			i++;
		}
	}
}
