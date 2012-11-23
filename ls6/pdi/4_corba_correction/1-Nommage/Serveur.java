import org.omg.CORBA.* ;
import org.omg.PortableServer.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

// Lancement du service de noms : tnameserv -ORBInitialPort 3000 &
// Lancement du serveur :         java Serveur localhost 3000 &

public class Serveur
{
	public static void main(String args[])
	{
		if (args.length != 2)
		{
	    System.out.println("Usage : java Serveur <machineServeurDeNoms> <port>") ;
	    return ;
		}
		try
		{
	    String [] argv = {"-ORBInitialHost", args[0], "-ORBInitialPort", args[1]} ; 
	    ORB orb = ORB.init( argv, null ) ;

	    EtudiantImpl et = new EtudiantImpl("Dupont", "Robert") ;

	    //initialiser le POA
	    POA poa = POAHelper.narrow( orb.resolve_initial_references("RootPOA")) ;
	    poa.the_POAManager().activate() ;
      org.omg.CORBA.Object poaobj = poa.servant_to_reference(et) ;

	    // ETAPE 1
	    org.omg.CORBA.Object obj = null ;
	    obj = orb.resolve_initial_references("NameService") ; 

	    if(obj == null)
			{
				System.out.println("Ref nil sur NameService") ;
				System.exit(1) ;
	    }

	    // ETAPE 2
	    org.omg.CosNaming.NamingContext nc = NamingContextHelper.narrow(obj) ;

	    // ETAPE 3
	    NameComponent[] aName = new NameComponent[1] ;
	    aName[0] = new NameComponent() ;
	    aName[0].id = "etudiant1" ;
	    aName[0].kind = "donnee" ;

	    // ETAPE 4
	    nc.rebind(aName, poaobj) ;
	    System.out.println("Le serveur est pret") ;
	    orb.run() ;
		}
    catch( org.omg.CORBA.SystemException ex ) { ex.printStackTrace() ; }
		catch( org.omg.CORBA.UserException ex ) { ex.printStackTrace() ; }
  }
}





