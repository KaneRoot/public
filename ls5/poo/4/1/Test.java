public class Test
{
	public static void main(String[] args)
	{
		int NB_THREADS = 3, i;
		CompteARebours c[] = new CompteARebours[NB_THREADS];

		for(i = 0 ; i < NB_THREADS ; i++)
			c[i] = new CompteARebours(i,i*2+1);

		for(i = 0 ; i < NB_THREADS ; i++)
			c[i].start();

		for(i = 0 ; i < NB_THREADS ; i++)
		{
			try{ c[i].join(); }
			catch(InterruptedException e)
			{ 
				System.out.println("ERREUR : " + e.getMessage());
			}
		}
	}
}
