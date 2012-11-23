import org.omg.CORBA.* ;
import org.omg.PortableServer.* ;
import java.util.* ;
import java.io.* ;

public class AnnuaireImpl 
	extends AnnuairePOA
{
	Hashtable numeros = new Hashtable() ;

  public AnnuaireImpl()
	{
		numeros.put("tintin", "06 76 70 80 09") ;
		numeros.put("milou", "06 50 40 36 76") ;
		numeros.put("tournesol", "06 07 33 72 06") ;
  }
    
  public void listerNoms (org.omg.CORBA.StringHolder liste)
	{
		String res = " " ;
		Iterator it = numeros.keySet().iterator() ;
		while (it.hasNext())
		{
	    String nom = (String) it.next() ;
	    res += nom + " : " + numeros.get(nom) + "\n " ;
		}
	
		liste.value = res;
  }

  public void chercheNom (String nom, org.omg.CORBA.StringHolder numero)
	{
		String resultat = (String) numeros.get(nom) ;
		if (resultat == null) resultat = "Nom inconnu : " + nom ;

		System.out.println(nom + " : " + resultat) ;
		numero.value = resultat ;
  }

  public static void main(String[] args)
	{
		try
		{
      //init ORB
	    ORB orb = ORB.init( args, null ) ;
	    
      AnnuaireImpl myobj = new AnnuaireImpl () ;

	    //initialiser le POA
	    POA poa = POAHelper.narrow( orb.resolve_initial_references("RootPOA")) ;

	    poa.the_POAManager().activate() ;

      org.omg.CORBA.Object poaobj = poa.servant_to_reference(myobj) ;

	    String ior = orb.object_to_string(poaobj) ;
	    FileOutputStream file = new FileOutputStream(iorfile.value) ;
	    PrintWriter out = new PrintWriter(file) ;
	    out.println(ior) ; out.flush() ;
	    file.close() ;
	    
 	    orb.run() ;
		}
		catch( Exception ex )
		{
			System.err.println("Erreur !!") ;
	    ex.printStackTrace() ;
		}
	}
}

