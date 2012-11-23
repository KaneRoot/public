import java.io.* ;
import org.omg.PortableServer.* ;

public class CompteImpl
  extends ComptePOA
{
  private float solde ;

  public CompteImpl()
  { 
    solde = 0 ;
  }
  
  public boolean deposeLiquide (float montant)
  { 
    solde += montant ; 
    return true ;
  }

  public boolean retireLiquide (float montant)
  { 
    float nouveau = solde - montant ;
    if (nouveau < 0.0)
      return false ;
    solde = nouveau ;
     return true ;
  }
  
  public float afficheMontant ()
  {
   return solde ;
  }
  
  public boolean virementCompteaCompte (Compte compte, float montant)
  {
    if (!retireLiquide(montant))
      return false ;
    compte.deposeLiquide(montant) ;
    return true ;
  } ;
}
