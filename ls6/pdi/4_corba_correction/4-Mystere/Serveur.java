import org.omg.CORBA.* ;
import org.omg.PortableServer.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

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
	    String [] argv = {"-ORBInitialHost",args[0],"-ORBInitialPort",args[1]} ; 
	    ORB orb = ORB.init( argv, null ) ; 

	    EtudiantImpl e1 = new EtudiantImpl("Smith", "John") ;
	    EtudiantImpl e2 = new EtudiantImpl("Lesmemealamaison", "Leon-Jay") ;
	    EtudiantImpl e3 = new EtudiantImpl("Ouille", "Jacques") ;

	    POA poa = POAHelper.narrow( orb.resolve_initial_references("RootPOA")) ;
	    poa.the_POAManager().activate() ;

	    org.omg.CORBA.Object obj = null ;
	    obj = orb.resolve_initial_references("NameService") ;
	    if(obj == null)
			{
				System.out.println("Reference nil sur `NameService'") ;
				System.exit(1) ;
	    }

	    org.omg.CosNaming.NamingContext nc=NamingContextHelper.narrow(obj) ;
	    if(nc == null)
			{
				System.out.println("Reference type nil sur `NameService'") ;
				System.exit(1) ;
	    }

	    NameComponent[] nc1Name = new NameComponent[1] ;
	    nc1Name[0] = new NameComponent("rep1", "") ;
	    NamingContext nc1 = nc.new_context() ;
	    nc.rebind_context(nc1Name,nc1) ;

	    NameComponent[] nc2Name = new NameComponent[1] ;
	    nc2Name[0] = new NameComponent("rep2", "") ;
	    NamingContext nc2 = nc.new_context() ;
	    nc.rebind_context(nc2Name,nc2) ;

	    NameComponent[] nc3Name = new NameComponent[1] ;
	    nc3Name[0] = new NameComponent("rep3", "") ;
	    NamingContext nc3 = nc.new_context() ;
	    nc1.rebind_context(nc3Name,nc3) ;
	    nc3.rebind_context(nc3Name,nc) ;
	    
	    NameComponent[] aName = new NameComponent[1] ;
	    aName[0] = new NameComponent("et1", "") ;
	    nc.bind(aName, poa.servant_to_reference(e1)) ;
	    nc1.bind(aName, poa.servant_to_reference(e1)) ;
	    System.out.println("et1 est publie en tant que et1 et rep1/et1") ;

	    aName[0] = new NameComponent("et2", "") ;
	    nc2.bind(aName, poa.servant_to_reference(e2)) ;
	    System.out.println("et2 est publie en tant que rep2/et2") ;

	    aName[0] = new NameComponent("et3", "") ;
	    nc3.bind(aName, poa.servant_to_reference(e3)) ;
	    System.out.println("et3 est publie en tant que rep1/rep3/et3") ;

	    System.out.println("Le serveur est pret ") ;
	    orb.run() ;
		}
		catch( Exception ex )
		{
  	  System.err.println( "Erreur !!" ) ;
  	  ex.printStackTrace() ;
		}
  }
}

