import java.util.*;
public interface Annuaire extends java.rmi.Remote
{
  String chercheNom(String nom) throws java.rmi.RemoteException ;
  void ajoute(String nom, String numero) throws java.rmi.RemoteException ;
  void supprime(String nom) throws java.rmi.RemoteException ;
  Hashtable lister() throws java.rmi.RemoteException;
}
