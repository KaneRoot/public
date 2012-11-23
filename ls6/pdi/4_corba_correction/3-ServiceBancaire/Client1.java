import org.omg.CORBA.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

public class Client1
{
  public static void main(String args[])
  { 
	  try
    {
	    ORB orb = ORB.init(new String[0], null ) ;

	    // ETAPE 3
	    String r1 = "corbaname::" + args[0] + ":" + args[1] + "#agence1/client1/c1" ;
	    String r2 = "corbaname::" + args[0] + ":" + args[1] + "#agence1/client1/c3" ;
	    String r3 = "corbaname::" + args[0] + ":" + args[1] + "#agence1/client2/c2" ;
	    String r4 = "corbaname::" + args[0] + ":" + args[1] + "#agence1/client2/c4" ;

	    // ETAPE 4
	    org.omg.CORBA.Object o1 = orb.string_to_object(r1) ; 
	    org.omg.CORBA.Object o2 = orb.string_to_object(r2) ; 
	    org.omg.CORBA.Object o3 = orb.string_to_object(r3) ; 
	    org.omg.CORBA.Object o4 = orb.string_to_object(r4) ;  
	    if ((o1 == null) || (o2 == null) || (o3 == null) || (o4 == null))
      {
        System.out.println("Acces impossible a l'objet corba") ;
        System.exit(1) ;
	    }

	    // ETAPE 5
	    Compte c1 = CompteHelper.narrow(o1) ;
	    Compte c2 = CompteHelper.narrow(o2) ;
	    Compte c3 = CompteHelper.narrow(o3) ;
	    Compte c4 = CompteHelper.narrow(o4) ;

	    c1.deposeLiquide(1) ;
      c2.deposeLiquide(2) ;
	    c3.deposeLiquide(3) ;
      c4.deposeLiquide(4) ;
  
      System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant() + " " + c3.afficheMontant() + " " + c4.afficheMontant()) ;
	    c1.retireLiquide(2) ;
      c2.retireLiquide(2) ; 
	    c3.retireLiquide(2) ;
      c4.retireLiquide(2) ;
	    System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant() + " " + c3.afficheMontant() + " " + c4.afficheMontant()) ;

	    c1.virementCompteaCompte (c2, 0.5f) ;
	    System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant()) ;
	    
	  }
    catch( Exception ex )
    {
	    System.err.println( "Erreur !!" ) ;
	    ex.printStackTrace() ;
  	}
  }
}

