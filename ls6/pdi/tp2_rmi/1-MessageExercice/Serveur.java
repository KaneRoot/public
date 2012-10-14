import java.net.* ;
import java.rmi.* ;

public class Serveur
{
	public static void main(String [] args)
	{
		if (args.length != 1)
		{
			System.out.println("Usage : java Serveur <port du rmiregistry>") ;
			System.exit(0) ;
		}
		try
		{
			System.out.println("Connexion au port : " + args[0]);
			MessageImpl objLocal = new MessageImpl () ;
			Naming.rebind( "//localhost:" + args[0] + "/Message" ,objLocal) ;
			System.out.println("Serveur pret") ;
		}
		catch (RemoteException re) { System.out.println(re) ; }
		catch (MalformedURLException e) { System.out.println(e) ; }
	}
}
