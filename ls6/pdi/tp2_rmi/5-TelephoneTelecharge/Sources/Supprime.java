import java.rmi.* ;

public class Supprime
{
	public static void main(String[] args)
	{
		if (args.length != 4)
		{
			System.out.println("Usage : java Supprime <machineServeur> <NoPort> <nom_a_supprimer> ") ;
			System.exit(0) ;
		}

		System.out.println("Supprime args : " + args[0] + " " + args[1] + " " + args[2] + " - " + args.length) ;

		if (System.getSecurityManager() == null)
		{
			System.setSecurityManager(new RMISecurityManager()) ;
		}
		try
		{
			Annuaire annuaire = (Annuaire) Naming.lookup("rmi://"+args[0]+":"+args[1]+"/LAnnuaire") ;
			annuaire.enleveNom(args[2]);
		}
		catch (Exception e)
		{
			System.out.println("Supprime : " + e.getMessage()) ;
			e.printStackTrace() ;
		}
	}
}
