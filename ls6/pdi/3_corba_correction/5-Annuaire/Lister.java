import java.io.* ;
import org.omg.CORBA.* ;

public class Lister
{
	public static void main(String args[])
	{
		try
		{
	    ORB orb = ORB.init( args, null ) ;
	    System.out.println( "0) ORB initialise'") ;

	    FileReader file = new FileReader(iorfile.value) ;
	    BufferedReader in = new BufferedReader(file) ;
	    String ior = in.readLine() ;
	    file.close() ;

//	    ior = getParameter("adresse");
	    System.out.println( "1) IOR lue : " + ior ) ;

	    org.omg.CORBA.Object obj = orb.string_to_object(ior) ;
	    Annuaire annuaire = AnnuaireHelper.narrow(obj) ;

	    StringHolder liste = new StringHolder() ;
	    annuaire.listerNoms(liste) ;
	    System.out.println(liste.value) ;
		}
		catch( Exception ex )
		{
			System.err.println( "Erreur !!" ) ;
	    ex.printStackTrace() ;
		}
  }
}

