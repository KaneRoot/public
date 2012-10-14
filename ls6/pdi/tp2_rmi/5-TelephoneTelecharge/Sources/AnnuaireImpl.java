import java.rmi.* ; 
import java.util.* ; 
import java.rmi.server.UnicastRemoteObject ;

public class AnnuaireImpl 
  extends UnicastRemoteObject
  implements Annuaire
  {
    Hashtable numeros = new Hashtable() ;

    public AnnuaireImpl() throws RemoteException
    {
	super() ;
	numeros.put("tintin", "06 76 70 80 09") ;
	numeros.put("milou", "06 50 40 36 76") ;
	numeros.put("tournesol", "06 07 33 72 06") ;
    }

    public String chercheNom(String nom)
      throws RemoteException
    {
      String resultat = (String) numeros.get(nom) ; 
      if (resultat == null) resultat = "Nom inconnu : " + nom ;
	return resultat;
    }

    public String listerNoms ()  throws RemoteException
    {
      String res = " " ;
      Iterator it = numeros.keySet().iterator() ;
      while (it.hasNext())
      {
	String nom = (String) it.next() ;
        res += nom + " : " + numeros.get(nom) + " \n " ;
      }
      System.out.println("J'envoie ma liste") ;
      return res ;
    }

    public void enleveNom(String nom)
      throws RemoteException { }

    public void ajouteNom(String nom, String num)
      throws RemoteException {}

    public static void main(String[] args)
    {
      if (System.getSecurityManager() == null)
      {
	System.setSecurityManager(new RMISecurityManager()) ;
      }
    try
    {
      AnnuaireImpl annuaire = new AnnuaireImpl () ;
      Naming.rebind("LAnnuaire", annuaire) ;
      System.out.println("Annuaire en service") ;
    }
    catch (Exception e)
    {
      System.out.println("AnnuaireImpl : " + e.getMessage()) ;
      e.printStackTrace() ;
    }
  }
}
