import java.rmi.* ; 
import java.net.MalformedURLException ; 
import java.net.InetAddress.* ;
import java.net.* ;

public class Lister {
    public static void main(String [] args) {
	if (args.length != 0) 
	    System.out.println("Usage : java Lister");
	else {
	    try {
		String hostname = (InetAddress.getLocalHost()).getHostName();
		Annuaire annuaire = (Annuaire)
		    Naming.lookup("rmi://"+hostname+"/LAnnuaire");
		System.out.println(annuaire.listerNoms());
	    }
	    catch (NotBoundException re) { System.out.println(re) ; }
	    catch (java.net.UnknownHostException re) { System.out.println(re) ; }
	    catch (RemoteException re) { System.out.println(re) ; }
	    catch (MalformedURLException e) { System.out.println(e) ; }
	}
    }
}
