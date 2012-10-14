import java.rmi.Remote ; 
import java.rmi.RemoteException ; 

public interface Message
  extends Remote
{
  public String messageDistant()
    throws RemoteException ;
  public Message clonage(String ch)
    throws RemoteException ;
}
