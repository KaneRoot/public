import java.rmi.Remote ;
import java.rmi.RemoteException ;

public interface OpMatrice extends Remote
{
  public int[][] multiplicationMatrice (int [][] a, int [][] b)
    throws RemoteException ;
}


