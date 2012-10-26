import java.rmi.* ; 
import java.net.MalformedURLException ; 
import java.net.InetAddress.* ;
import java.net.* ;

public class Ajoute {
    public static void main(String [] args) {
	if (args.length != 2) 
	    System.out.println("Usage : java Ajoute <nom> <telephone>");
	else {
	    try {
	    String hostname = (InetAddress.getLocalHost()).getHostName();
	    Annuaire annuaire = (Annuaire)
		Naming.lookup("rmi://"+hostname+"/LAnnuaire");
	    annuaire.ajouteNom(args[0],args[1]);
	    System.out.println("Ajoute : "+args[0]+" "+args[1]);
	    }
	    catch (NotBoundException re) { System.out.println(re) ; }
	    catch (java.net.UnknownHostException re) { System.out.println(re) ; }
	    catch (RemoteException re) { System.out.println(re) ; }
	    catch (MalformedURLException e) { System.out.println(e) ; }
	}
    }
}
