import java.rmi.* ; 
import java.net.InetAddress.* ;
import java.net.* ;

public class Client
{
	public final static int A = 10;
	public final static int B = 10;
	OpMatrice opMatrice;

	public static void afficher_matrice(int[][] x)
	{
		System.out.println();
		for(int i = 0 ; i < x.length ; i++)
		{
			for(int j = 0 ; j < x[0].length ; j++)
			{
				System.out.print(" " + x[i][j] + " : " );
			}
			System.out.println();
		}
		System.out.println();
	}

	public static void main(String[] args)
	{
		int[][] a = new int[A][B];
		int[][] b = new int[A][B];
		System.out.println(" a ");
		afficher_matrice(a);
		System.out.println(" b ");
		afficher_matrice(b);

		for(int i = 0 ; i < A ; i++)
			for(int j = 0 ; j < B ; j++)
			{
				a[i][j] = ((1 + i * j) % 5) * 3;
				b[i][j] = ((1 + i * j) * 3) % 6;
			}

		try
		{
			opMatrice = (OpMatrice) Naming.lookup("rmi://"+args[0]+":"+args[1]+"/OpMatrice") ;
			int[][] resultat = opMatrice.sommeMatrice(a,b);
			System.out.println(" resultat ");
			afficher_matrice(resultat);
		}
		catch (Exception e)
		{
			System.err.println(e) ;
			e.printStackTrace();
		}
	}
}
