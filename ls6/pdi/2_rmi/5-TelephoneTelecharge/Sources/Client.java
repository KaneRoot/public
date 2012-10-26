import java.rmi.* ;

public class Client
{
	public static void main(String[] args)
	{
		System.out.println("Client args : " + args[0] + " " + args[1] + "-" + args.length) ;
		if (args.length != 2)
		{
			System.out.println("Usage : java Client <machineServeur> <NoPort>") ;
			System.exit(0) ;
		}
		if (System.getSecurityManager() == null)
		{
			System.setSecurityManager(new RMISecurityManager()) ;
		}
		try
		{
			Annuaire annuaire = (Annuaire) Naming.lookup("rmi://"+args[0]+":"+args[1]+"/LAnnuaire") ;
			System.out.println("Liste annuaire\n"+annuaire.listerNoms()) ;
		}
		catch (Exception e)
		{
			System.out.println("Client : " + e.getMessage()) ;
			e.printStackTrace() ;
		}
	}
}
