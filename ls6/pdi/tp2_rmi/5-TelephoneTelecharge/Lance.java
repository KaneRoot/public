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
    
    String base = "http://" + args[0] + ":" + args[1] +"/" ;
    System.setProperty("java.security.policy","java.policy") ;
    
    if (System.getSecurityManager() == null)
    {
      System.setSecurityManager(new RMISecurityManager()) ;
    }
    try
    {
      java.net.URL codebase = new java.net.URL(base) ;
      Class prog = java.rmi.server.RMIClassLoader.loadClass(codebase, args[2]) ;
      Class [] mainargs = {args.getClass()} ;
      java.lang.reflect.Method method = prog.getDeclaredMethod("main", mainargs) ;
      String[] anArray = new String[args.length-3] ;
      for (int i = 0; i < anArray.length; i++)
      {
	anArray[i] = args[i+3] ;
      }
      Object arguments[] = {anArray} ;
      method.invoke(null,arguments) ;

    }
    catch (Exception e)
    {
      System.out.println("Lance Exception: " + e.getMessage()) ;
      e.printStackTrace() ;
    }
  }
}

