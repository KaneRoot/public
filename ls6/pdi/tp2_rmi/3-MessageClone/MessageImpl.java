import java.rmi.server.UnicastRemoteObject ;
import java.rmi.RemoteException ;
import java.net.InetAddress.* ;
import java.net.* ;

public class MessageImpl 
  extends UnicastRemoteObject
  implements Message 
{
  private String chaine = "l'original sur " ;

  public MessageImpl ()
    throws RemoteException 
  {
    super() ;
  } ;

  public MessageImpl (String ch)
    throws RemoteException 
  {
    super() ;
    chaine = ch ;
  } ;
    
  public String messageDistant()
    throws RemoteException
  { 
    String output=null;
    try
    {
      output = chaine + (InetAddress.getLocalHost()).getHostName() ;
    } 
    catch (Exception e) {} ;
    return(output) ;
  }

  public Message clonage(String ch)
    throws RemoteException
  { 
    return(new MessageImpl(ch)) ;
  }
}
