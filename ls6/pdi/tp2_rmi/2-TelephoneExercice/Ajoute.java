import java.rmi.* ; 
import java.net.MalformedURLException ; 

public class Ajoute
{
	public static void main(String [] args)
	{
		if (args.length != 2)
		{
			System.out.println("Usage : java Ajoute <nom> <numero>"); //<machine du Serveur> <port du rmiregistry>") ;
			System.exit(0) ;
		}
		try
		{
			Annuaire a;
			a = (Annuaire) Naming.lookup("//localhost:10000/LAnnuaire");
			a.ajoute(args[0], args[1]) ; 
		}
		catch (NotBoundException re) { System.out.println(re) ; }
		catch (RemoteException re) { System.out.println(re) ; }
		catch (MalformedURLException e) { System.out.println(e) ; }
	}
}
