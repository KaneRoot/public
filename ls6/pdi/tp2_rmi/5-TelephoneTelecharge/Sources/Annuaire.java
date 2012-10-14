public interface Annuaire
  extends java.rmi.Remote
{
  String chercheNom(String nom)
    throws java.rmi.RemoteException ;

  public void ajouteNom(String nom, String num)
    throws java.rmi.RemoteException ;

  public String listerNoms ()
    throws java.rmi.RemoteException ;

  public void enleveNom(String nom)
    throws java.rmi.RemoteException;
}
