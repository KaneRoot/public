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
	try {
	    Couleur c = (Couleur) Naming.lookup("rmi://" + args[0] + ":" + args[1] + "/Couleur") ;
	    // a partir d'ici, on peut utiliser c comme un objet local
	    c.setColorRGB(0, 0, 255) ;
	    System.out.println("La valeur RGB=" + c.printRGB() + " équivaut à " + c.printCMY() + " en CMY") ;
	}
	catch (NotBoundException re)    { System.out.println(re) ; }
	catch (RemoteException re)      { System.out.println(re) ; }
	catch (MalformedURLException e) { System.out.println(e) ;  }
    }
}
