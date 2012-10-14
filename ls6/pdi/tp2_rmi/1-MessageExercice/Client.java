import java.rmi.* ; 
import java.net.MalformedURLException ; 

public class Client
{
	public static void main(String [] args)
	{
		if (args.length != 2)
		{
			System.out.println("Usage : java Client <machine du Serveur> <port du rmiregistry>") ;
			System.exit(0) ;
		}
		try
		{
			Message b = (Message) Naming.lookup("//" + args[1] + "/Message") ;
			System.out.println("Le client recoit : " + b.messageDistant()) ; 
		}
		catch (NotBoundException re) { System.out.println(re) ; }
		catch (RemoteException re) { System.out.println(re) ; }
		catch (MalformedURLException e) { System.out.println(e) ; }
	}
}
