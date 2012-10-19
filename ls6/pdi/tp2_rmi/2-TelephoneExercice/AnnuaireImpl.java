import java.rmi.* ; 
import java.util.* ; 
import java.rmi.server.UnicastRemoteObject ;

public class AnnuaireImpl extends UnicastRemoteObject implements Annuaire
{
	Hashtable numeros = new Hashtable() ;

	public AnnuaireImpl() throws RemoteException
	{
		super() ;
		numeros.put("tintin", "06 76 70 80 09") ;
		numeros.put("milou", "06 50 40 36 76") ;
		numeros.put("tournesol", "06 07 33 72 06") ;
	}
	public void ajoute(String nom, String num) throws RemoteException
	{
		numeros.put(nom,num) ;
	}
	public void supprime(String nom) throws RemoteException
	{
		numeros.remove(nom) ;
	}

	public String chercheNom(String nom) throws RemoteException
	{
		String resultat = (String) numeros.get(nom) ;
		if (resultat == null)
			resultat = "Nom inconnu : " + nom ;
		return resultat ;
	}

	public static void main(String[] args)
	{
		try
		{
			AnnuaireImpl annuaire = new AnnuaireImpl () ;
			Naming.rebind("rmi://localhost:" + args[0] + "/LAnnuaire", annuaire) ;
			System.out.println("Annuaire en service") ;
		}
		catch (Exception e)
		{
			System.out.println("AnnuaireImpl : " + e.getMessage()) ;
			e.printStackTrace();
		}
	}
}
