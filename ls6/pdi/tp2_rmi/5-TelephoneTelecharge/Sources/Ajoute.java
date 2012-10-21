import java.rmi.* ;

public class Ajoute
{
	public static void main(String[] args)
	{
		System.out.println("Ajoute args : " + args[0] + " " + args[1] + " " + args[2] + " " + args[3] + " - " + args.length) ;
		if (args.length != 4)
		{
			System.out.println("Usage : java Ajoute <machineServeur> <NoPort> <nom_a_ajouter> <numero>") ;
			System.exit(0) ;
		}
		if (System.getSecurityManager() == null)
		{
			System.setSecurityManager(new RMISecurityManager()) ;
		}
		try
		{
			Annuaire annuaire = (Annuaire) Naming.lookup("rmi://"+args[0]+":"+args[1]+"/LAnnuaire") ;
			annuaire.ajouteNom(args[2], args[3]);
		}
		catch (Exception e)
		{
			System.out.println("Ajoute : " + e.getMessage()) ;
			e.printStackTrace() ;
		}
	}
}
