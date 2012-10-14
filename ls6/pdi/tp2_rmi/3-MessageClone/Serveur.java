import java.net.* ;
import java.rmi.* ;

public class Serveur
{
   public static void main(String [] args)
    {
      try
      {
	MessageImpl objLocal = new MessageImpl () ;
	Naming.rebind("rmi://localhost/Message",objLocal) ;
	System.out.println("Serveur pret") ;
      }
      catch (RemoteException re) { System.out.println(re) ; }
      catch (MalformedURLException e) { System.out.println(e) ; }
  }
}
