import java.rmi.* ; 
import java.net.MalformedURLException ; 

public class Client
{
  public static void main(String [] args)
  {
    if (args.length != 1) 
      System.out.println("Usage : java Client <machine du Serveur>") ;
    else
    {
      try
      {
	Message b =(Message) Naming.lookup("rmi://" + args[0] + "/Message") ;
	Message c = b.clonage("le clone sur ") ;
	System.out.println("Le client recoit : " + b.messageDistant()) ; 
	System.out.println("Le client recoit : " + c.messageDistant()) ; 
      }

      catch (NotBoundException re) { System.out.println(re) ; }
      catch (RemoteException re) { System.out.println(re) ; }
      catch (MalformedURLException e) { System.out.println(e) ; }
    }
  }
}
