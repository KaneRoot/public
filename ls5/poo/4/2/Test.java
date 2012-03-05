public class Test
{
	public static void main(String[] args)
	{
		Reserve r = new Reserve();
		Consommateur c = new Consommateur(r);
		Producteur p = new Producteur(r);

		c.start();
		p.start();

		try
		{
			c.join();
			p.join();
		}
		catch(Exception e)
		{
			System.out.println("Exception join : " + e.getMessage());
		}
	}

}
