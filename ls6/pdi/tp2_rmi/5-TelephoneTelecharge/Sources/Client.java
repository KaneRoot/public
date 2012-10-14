import java.rmi.* ;

public class Client
{
  public static void main(String[] args)
  {
    if (args.length != 1)
    {
      System.out.println("Usage : java Client <machineServeur>") ;
      System.exit(0) ;
    }
    System.out.println("Client args : " + args[0] + "-" + args.length) ;
    if (System.getSecurityManager() == null)
    {
      System.setSecurityManager(new RMISecurityManager()) ;
    }
    try
    {
      Annuaire annuaire = (Annuaire) Naming.lookup("rmi://"+args[0]+"/LAnnuaire") ;
      System.out.println("Liste annuaire\n"+annuaire.listerNoms()) ;
    }
    catch (Exception e)
    {
      System.out.println("Client : " + e.getMessage()) ;
      e.printStackTrace() ;
    }
  }
}
