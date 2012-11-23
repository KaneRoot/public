import org.omg.CORBA.* ;
import org.omg.CosNaming.* ;
import java.io.* ;

public class Client
{
  public static void main(String args[])
  { 
    try
    {
      ORB orb = ORB.init(new String[0], null ) ;

      // ETAPE 3
      String r1 = "corbaname::" + args[0] + ":" + args[1] + "#c1" ;
      String r2 = "corbaname::" + args[0] + ":" + args[1] + "#c2" ;
      
      // ETAPE 4
      org.omg.CORBA.Object o1 = orb.string_to_object(r1) ; 
      org.omg.CORBA.Object o2 = orb.string_to_object(r2) ; 

      if ((o1 == null) || (o2 == null))
      {
        System.out.println("Acces impossible a l'objet corba") ;
	System.exit(1) ;
      }

      // ETAPE 5
      Compte c1 = CompteHelper.narrow(o1) ;
      Compte c2 = CompteHelper.narrow(o2) ;
 
      c1.deposeLiquide(3) ;
      c2.deposeLiquide(2) ;

      System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant()) ;
   
      c1.retireLiquide(1) ;
      c2.retireLiquide(3) ;

      System.out.println(" Resultat trouve " + c1.afficheMontant() + " " + c2.afficheMontant()) ;
   
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

