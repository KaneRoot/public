import java.rmi.* ; 
import java.net.InetAddress.* ;
import java.net.* ;

public class Client
{
	public final static int A = 2;
	public final static int B = 2;
	public static OpMatrice opMatrice;

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

		if(args.length != 2)
		{
			System.out.println("Usage : java Client <serveur> <port>");
			System.exit(-1);
		}

		int[][] a = new int[A][B];
		int[][] b = new int[A][B];

		for(int i = 0 ; i < A ; i++)
			for(int j = 0 ; j < B ; j++)
			{
				a[i][j] = ((1 + i * j) % 5) * 3;
				b[i][j] = ((1 + i * j) * 3) % 6;
			}

		System.out.println(" a ");
		afficher_matrice(a);
		System.out.println(" b ");
		afficher_matrice(b);
		try
		{
			opMatrice = (OpMatrice) Naming.lookup("rmi://"+args[0]+":"+args[1]+"/OpMatrice") ;
			int[][] resultatsomme = opMatrice.sommeMatrice(a,b);
			int[][] resultatmultiplication = opMatrice.multiplicationMatrice(a,b);
			System.out.println(" resultat somme ");
			afficher_matrice(resultatsomme);

			System.out.println(" resultat multiplication ");
			afficher_matrice(resultatmultiplication);
		}
		catch (Exception e)
		{
			System.err.println(e) ;
			e.printStackTrace();
		}
	}
}
