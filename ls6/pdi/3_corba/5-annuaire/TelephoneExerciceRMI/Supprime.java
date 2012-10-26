import java.rmi.* ; 
import java.net.MalformedURLException ; 
import java.net.InetAddress.* ;
import java.net.* ;

public class Supprime {
    public static void main(String [] args) {
	if (args.length != 1) 
	    System.out.println("Usage : java Supprime <nom>");
	else {
	    try {
	    String hostname = (InetAddress.getLocalHost()).getHostName();
	    Annuaire annuaire = (Annuaire)
		Naming.lookup("rmi://"+hostname+"/LAnnuaire");
	    System.out.println("Supprime : "+args[0]);
	    annuaire.enleveNom(args[0]);
	    }
	    catch (java.net.UnknownHostException re) { System.out.println(re) ; }
	    catch (NotBoundException re) { System.out.println(re) ; }
	    catch (RemoteException re) { System.out.println(re) ; }
	    catch (MalformedURLException e) { System.out.println(e) ; }
	}
    }
}
