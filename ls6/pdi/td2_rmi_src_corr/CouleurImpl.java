import java.rmi.server.UnicastRemoteObject ;
import java.rmi.RemoteException ;

public class CouleurImpl 
    extends UnicastRemoteObject
    implements Couleur
    {

    public int R ;
    public int G ;
    public int B ;
    
    public CouleurImpl () throws RemoteException
    {
       super() ;
    } ;
    public void setColorRGB(int Red, int Green, int Blue) throws RemoteException
    {
	R = Red ;
	G = Green ;
	B = Blue ;
    }
    public void setColorCMY(int Cyan, int Magenta, int Yellow) throws RemoteException
    {
	R = 255 - Cyan ;
	G = 255 - Magenta ;
	B = 255 - Yellow ;
    }
    public String printRGB() throws RemoteException
    { 
	return("(" + R + "," + G + "," + B + ")" );
    }
    public String printCMY() throws RemoteException
    { 
	return("(" + (255-R) + "," + (255-G) + "," + (255-B) + ")" );
    }
}
