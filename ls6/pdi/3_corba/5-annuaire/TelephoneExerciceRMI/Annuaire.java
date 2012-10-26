public interface Annuaire extends java.rmi.Remote {
    String chercheNom(String nom) throws java.rmi.RemoteException;
    void enleveNom(String nom) throws java.rmi.RemoteException;
    void ajouteNom(String nom, String num) throws java.rmi.RemoteException; 
    String listerNoms() throws java.rmi.RemoteException; 
}
