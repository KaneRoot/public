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
      System.out.println("Usage : java Serveur <machineServeurDeNoms> <NoPort> ") ;
      return ;
    }
    try
    {
      String [] argv = {"-ORBInitialHost", args[0], "-ORBInitialPort", args[1] } ;
      ORB orb = ORB.init( argv, null ) ; 
      CompteImpl c1 = new CompteImpl() ;
      CompteImpl c2 = new CompteImpl() ;
      CompteImpl c3 = new CompteImpl() ;
      CompteImpl c4 = new CompteImpl() ;

      //initialiser le POA
      POA poa = POAHelper.narrow(orb.resolve_initial_references( "RootPOA" )) ;
      poa.the_POAManager().activate() ;

      // ETAPE 1
      org.omg.CORBA.Object obj = null ;
      obj = orb.resolve_initial_references("NameService") ;

      if(obj == null)
      { 
        System.out.println("Ref nil sur NameService"); System.exit(1);
      }

      // ETAPE 2
      org.omg.CosNaming.NamingContext nc=NamingContextHelper.narrow(obj) ;
      System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant()) ;

      // ETAPE 3
      NameComponent[] nc1Name = new NameComponent[1] ;
      nc1Name[0] = new NameComponent("agence1","") ;
  
      NamingContext nc1 = nc.new_context() ;
      nc.rebind_context(nc1Name,nc1) ;

      NameComponent[] nc2Name = new NameComponent[1] ;
      nc2Name[0] = new NameComponent("client1","") ;

      NamingContext nc2 = nc1.new_context() ;
      nc1.rebind_context(nc2Name,nc2) ;

      NameComponent[] nc3Name = new NameComponent[1] ;
      nc3Name[0] = new NameComponent("client2","") ;

      NamingContext nc3 = nc1.new_context() ;
      nc1.rebind_context(nc3Name,nc3) ;

      NameComponent[] aName = new NameComponent[1] ;
      aName[0] = new NameComponent() ;
      aName[0].id = "c1" ;
      aName[0].kind = "" ;

      org.omg.CORBA.Object poaobj = poa.servant_to_reference(c1) ;
      nc2.bind(aName, poaobj) ;
      aName[0].id = "c2" ;
      aName[0].kind = "" ;
      poaobj = poa.servant_to_reference(c2) ;
      nc3.bind(aName, poaobj) ;

      aName[0].id = "c3" ;
      aName[0].kind = "" ;
      poaobj = poa.servant_to_reference(c3) ;
      nc2.bind(aName, poaobj) ;

      aName[0].id = "c4" ;
      aName[0].kind = "" ;
      poaobj = poa.servant_to_reference(c4) ;
      nc3.bind(aName, poaobj) ;

      System.out.println("Le serveur est pret ") ;
      orb.run() ;
    }
    catch( Exception ex )
    {
      System.err.println( "Erreur !!"+ ex.getMessage() ) ; 
      ex.printStackTrace() ;
    }
  }   
}

