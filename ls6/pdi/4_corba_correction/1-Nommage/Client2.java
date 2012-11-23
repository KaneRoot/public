import org.omg.CORBA.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

public class Client2
{
  public static void main(String args[])
	{
		try
		{
			if (args.length != 2)
			{
				System.out.println("Usage : java Client2 <machineServeurDeNoms> <port>") ;
				return ;
			}
	
			ORB orb = ORB.init(new String[0], null ) ;

  	 	// ETAPE 3
  	 	String reference = "corbaname::" + args[0] + ":" + args[1] + "#etudiant1.donnee" ;
  	 	System.out.println("Je cherche : " + reference) ;

  	 	// ETAPE 4
  	 	org.omg.CORBA.Object obj = orb.string_to_object(reference) ; 
			if(obj == null)
			{
				System.out.println("Acces impossible a l'objet corba") ;
				System.exit(1) ;
  	  }

			// ETAPE 5
		  Etudiants.Etudiant et = Etudiants.EtudiantHelper.narrow(obj) ;
			if(et == null)
			{
				System.err.println("Erreur sur narrow() ") ;
				System.exit(0) ;
			}
		  System.out.println(" Resultat trouve : " + et.nom() + " " + et.prenom()) ;
		} 
  	catch( org.omg.CORBA.SystemException ex ) { ex.printStackTrace() ; }
  }
}

