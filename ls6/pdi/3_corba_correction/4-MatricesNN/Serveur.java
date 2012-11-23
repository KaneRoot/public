import java.io.* ;
import org.omg.CORBA.* ;
import org.omg.PortableServer.* ;

public class Serveur
{
  public static void main(String[] args)
  {
    try
    {
      // init ORB
      ORB orb = ORB.init( args, null ) ;
      OpMatriceImpl myobj = new OpMatriceImpl() ;

      // Déclarer POA
      POA poa = POAHelper.narrow( orb.resolve_initial_references("RootPOA")) ;

      // Activer le POAmanager
      poa.the_POAManager().activate() ;

      // Référence d'objet poa
      org.omg.CORBA.Object poaobj = poa.servant_to_reference(myobj) ;

      // Identifiant IOR de cet objet
      String ior = orb.object_to_string(poaobj) ;

      FileOutputStream file = new FileOutputStream(iorfile.value) ;
      PrintWriter out = new PrintWriter(file) ;
      out.println(ior) ; out.flush() ;
      file.close() ;
        
      orb.run() ;
    }
    catch( org.omg.CORBA.SystemException ex ) {  ex.printStackTrace() ; }
    catch( org.omg.CORBA.UserException ex ) { ex.printStackTrace() ; }
    catch( java.io.IOException ex) {  ex.printStackTrace() ; }
  }
}

