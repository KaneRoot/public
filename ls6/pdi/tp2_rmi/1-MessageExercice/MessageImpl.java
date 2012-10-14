import java.rmi.server.UnicastRemoteObject ;
import java.rmi.RemoteException ;

public class MessageImpl extends UnicastRemoteObject implements Message
{  
	public MessageImpl () throws RemoteException
	{
		super() ;
	}

	public String messageDistant() throws RemoteException
	{ 
		return( "coucou" ) ;
	}
}
