import java.rmi.Remote ; 
import java.rmi.RemoteException ; 

public interface Couleur extends Remote
{
	public void setColorRGB(int Red, int Green, int Blue) throws RemoteException ;
	public void setColorCMY(int Cyan, int Magenta, int Yellow) throws RemoteException ;
	public String printRGB() throws RemoteException ;
	public String printCMY() throws RemoteException ;
}
