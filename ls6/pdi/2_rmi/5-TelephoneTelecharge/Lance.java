import java.rmi.RMISecurityManager ;
import java.rmi.server.RMIClassLoader ;

public class Lance
{
	public static void main(String[] args)
	{
		if (args.length < 3)
		{
			System.out.println("Usage : java Lance <ServeurDeClasses> <noPort> <classeALancer> <NoPortRMIreg> <progArgs>") ;
			System.exit(0) ;
		}

		// Serveur sur lequel on se connecte pour récupérer la classe
		String base = "http://" + args[0] + ":" + args[1] +"/" ;
		System.setProperty("java.security.policy","java.policy") ;

		// Si nous n'avons pas de gestionnaire de sécurité on en crée un
		if (System.getSecurityManager() == null)
		{
			System.setSecurityManager(new RMISecurityManager()) ;
		}
		try
		{
			// Création d'un objet java.net.URL (où se situe le ClassFileServer)
			java.net.URL codebase = new java.net.URL(base) ;
			// Demande de la classe que l'on souhaite charger à l'URL crée précédemment
			Class prog = java.rmi.server.RMIClassLoader.loadClass(codebase, args[2]) ;

			// pour tous les arguments, on recherche les classes.
			Class [] mainargs = {args.getClass()} ;
			java.lang.reflect.Method method = prog.getDeclaredMethod("main", mainargs) ;

			// On récupère les arguments de la ligne de commande
			// qui sont destinés à la classe appelée
			String[] anArray = new String[args.length-3] ;
			for (int i = 0; i < anArray.length; i++)
			{
				anArray[i] = args[i+3] ;
			}
			// Création d'objets (chaînes de caractères) qui sont les arguments reçu sur la ligne de commande
			Object arguments[] = {anArray} ;

			// Appel de la classe reçue avec les arguments 3 à args.length - 3
			method.invoke(null,arguments) ;

		}
		catch (Exception e)
		{
			System.out.println("Lance Exception: " + e.getMessage()) ;
			e.printStackTrace() ;
		}
	}
}

