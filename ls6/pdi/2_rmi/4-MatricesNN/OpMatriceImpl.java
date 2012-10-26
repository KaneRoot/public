import java.rmi.* ; 
import java.util.* ; 
import java.rmi.server.UnicastRemoteObject ;

public class OpMatriceImpl extends UnicastRemoteObject implements OpMatrice
{
	public OpMatriceImpl() throws RemoteException
	{
		super() ;
	}
	public int[][] sommeMatrice(int[][] a, int[][] b) throws RemoteException
	{
		int[][] somme = new int[a.length][a[0].length];
		int i, j;

		for(i = 0 ; i < a.length ; i++)
			for(j = 0 ; j < a[0].length ; j++)
				somme[i][j] = a[i][j] + b[i][j];

		return somme;
	}
	public int[][] multiplicationMatrice(int[][] a, int[][] b) throws RemoteException
	{
		int[][] mult = new int[a.length][b[0].length];
		int i, j, k, somme;
		for(i = 0 ; i < a.length ; i++)
			for(j = 0 ; j < b[0].length ; j++)
			{
				somme = 0;
				for(k = 0 ; k < a.length ; k++)
					somme += a[i][k] * b[k][j];

				mult[i][j] = somme;
			}
		return mult;
	}
	public static void main(String[] args)
	{
		if(args.length != 1)
		{
			System.out.println("Usage : java OpMatriceImpl <port>");
			System.exit(-1);
		}
		try
		{
			OpMatriceImpl opMatrice = new OpMatriceImpl () ;
			Naming.rebind("rmi://0.0.0.0:" + args[0] + "/OpMatrice", opMatrice) ;
			System.out.println("OpMatrice en service") ;
		}
		catch (Exception e)
		{
			System.out.println("OpMatriceImpl : " + e.getMessage()) ;
			e.printStackTrace();
		}
	}
}
