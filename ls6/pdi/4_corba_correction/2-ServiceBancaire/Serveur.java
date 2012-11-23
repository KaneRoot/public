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
      System.out.println("Usage : java Serveur <serveurDeNoms> <No port>") ;
      return ;
    }
    try
    {
      String [] argv = {"-ORBInitialHost", args[0], "-ORBInitialPort", args[1] } ; 
   
      ORB orb = ORB.init( argv, null ) ; 

      CompteImpl c1 = new CompteImpl() ;
      CompteImpl c2 = new CompteImpl() ;

      //initialiser le POA
      POA poa = POAHelper.narrow(orb.resolve_initial_references( "RootPOA" )) ;
      poa.the_POAManager().activate() ;

      // ETAPE 1
      org.omg.CORBA.Object obj = null ;
  
      obj = orb.resolve_initial_references("NameService") ; 
      if(obj == null)
      { 
        System.out.println("Ref nil sur NameService") ;
        System.exit(1) ;
      }

      // ETAPE 2
      org.omg.CosNaming.NamingContext nc=NamingContextHelper.narrow(obj) ;
      System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant()) ;
  
      // ETAPE 3
      NameComponent[] aName = new NameComponent[1] ;
      aName[0] = new NameComponent() ;
      aName[0].id = "c1" ;
      aName[0].kind = "" ;
  
      org.omg.CORBA.Object poaobj = poa.servant_to_reference( c1 ) ;
      nc.rebind(aName, poaobj) ;

      aName[0].id = "c2" ;
      aName[0].kind = "" ;
    
      poaobj = poa.servant_to_reference(c2) ;
      nc.rebind(aName, poaobj) ;

      System.out.println("Le serveur est pret ") ;
      orb.run() ;
    }
    catch( Exception ex )
    {
      System.err.println( "Erreur !!" + ex.getMessage() ) ; 
      ex.printStackTrace() ;
    }
  }   
}

