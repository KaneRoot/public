import org.omg.CORBA.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

public class Client
{
  public static void main(String args[])
	{
		try
		{
			if (args.length != 2)
			{
				System.out.println("Usage : java Client1 <machineServeurDeNoms> <port>") ;
				return ;
	    }
	
	    String [] argv = {"-ORBInitialHost", args[0], "-ORBInitialPort", args[1]} ; 
	    ORB orb = ORB.init( argv, null ) ; 

	    // ETAPE 1
	    org.omg.CORBA.Object obj = null ;
	    obj = orb.resolve_initial_references("NameService") ;
	    if(obj == null)
			{
				System.out.println("Reference nil sur `NameService'") ;
				System.exit(1) ;
	    }

	    // ETAPE 2
	    NamingContext nc = NamingContextHelper.narrow(obj) ;

	    // ETAPE 3
	    NameComponent[] aName = new NameComponent[1] ;
	    aName[0] = new NameComponent() ;
	    aName[0].id = "etudiant1" ;
	    aName[0].kind = "donnee" ;

	    // ETAPE 4
	    obj = nc.resolve(aName) ;

	    // ETAPE 5
	    Etudiants.Etudiant et = Etudiants.EtudiantHelper.narrow(obj) ;
	    if(et==null)
			{
				System.err.println("Erreur sur narrow() ") ;
				System.exit(0) ;
	    }
	    System.out.println("Etudiant1 : " + et.nom() + " " + et.prenom()) ;
		} 
		catch( org.omg.CORBA.SystemException ex ) { ex.printStackTrace() ; }
		catch( org.omg.CORBA.UserException ex ) { ex.printStackTrace() ; }
  }
}
