import org.omg.CORBA.* ;

public class Serveur
{
  public static void main(String[] args)
  {
    try
    {
      //init ORB
      ORB orb = ORB.init(args, null ) ;
      
      IcarreImpl myobj = new IcarreImpl() ;
      String ior = orb.object_to_string( myobj ) ;
      System.out.println( ior ) ;

      orb.run() ;
    }

    catch( org.omg.CORBA.SystemException ex ) { ex.printStackTrace() ; }
    //	catch( org.omg.CORBA.UserException ex ) { ex.printStackTrace();}
  }
}
