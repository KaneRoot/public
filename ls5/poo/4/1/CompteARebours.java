public class CompteARebours extends Thread
{
	public static int NB_SEC_ATTENTE = 1;
	public int id, nbEtapes;
	public CompteARebours(int identifiant, int nbEtapes)
	{
		super();
		this.id = identifiant;
		this.nbEtapes = nbEtapes;
	}

	@Override
	public void run()
	{
		for(int i = 0;  i < nbEtapes ; i++)
		{
			try { Thread.sleep(NB_SEC_ATTENTE * 1000); }
			catch( InterruptedException e)
			{
				System.out.println("ERREUR : " + e.getMessage());
			}

			System.out.println("Thread id : " + id + " étape numéro : " + i);
		}
	}
}
