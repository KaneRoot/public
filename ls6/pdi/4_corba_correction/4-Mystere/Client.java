import org.omg.CORBA.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

// Exemple d'utilisation : java Client localhost 3000 et1

public class Client
{
  public static void main(String args[])
	{ 
		try
		{
	    if (args.length != 3)
			{
				System.out.println("Usage : java Client2 <machineServeurDeNoms> <port> <nomDeLObjet>") ;
				return ;
	    }
	    ORB orb = ORB.init(new String[0], null ) ;
	    String reference = "corbaname::" + args[0] + ":" + args[1] + "#"+args[2] ;
	    System.out.println("Je cherche : " + reference) ;
	    org.omg.CORBA.Object obj = orb.string_to_object(reference) ; 

	    if(obj == null)
			{
				System.out.println("Acces impossible a l'objet corba") ;
				System.exit(1) ;
	    }

	    Etudiants.Etudiant et = Etudiants.EtudiantHelper.narrow(obj) ;
	    if(et == null)
			{
				System.err.println("Erreur sur narrow() ") ;
				System.exit(0) ;
	    }
	
	    System.out.println(" Resultat trouve' : " + et.nom() + " " + et.prenom()) ;
		}
		catch( Exception ex )
		{
			System.err.println( "Erreur !!" ) ;
		  ex.printStackTrace() ;
		}
  }
}

