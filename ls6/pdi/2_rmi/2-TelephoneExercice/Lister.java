import java.rmi.* ; 
import java.net.MalformedURLException ; 
import java.util.*;

public class Lister
{
	public static void main(String [] args)
	{
		Hashtable numeros;
		Iterator it;
		if (args.length != 0)
		{
			System.out.println("Usage : java Lister");
			System.exit(0) ;
		}
		try
		{
			Annuaire a;
			a = (Annuaire) Naming.lookup("//localhost:10000/LAnnuaire");
			numeros = a.lister();
			it = numeros.keySet().iterator();

			while(it.hasNext())
			{
				String next = (String) it.next();
				System.out.println("" + next + " : " + numeros.get(next));
			}
		}
		catch (NotBoundException re) { System.out.println(re) ; }
		catch (RemoteException re) { System.out.println(re) ; }
		catch (MalformedURLException e) { System.out.println(e) ; }
	}
}
