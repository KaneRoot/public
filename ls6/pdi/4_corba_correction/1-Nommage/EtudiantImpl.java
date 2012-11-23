import Etudiants.EtudiantPOA ;
import java.io.* ;

public class EtudiantImpl
	extends EtudiantPOA
{
  private String att_nom ;
  private String att_prenom ;
    
  public EtudiantImpl(String nom, String prenom)
	{
		att_nom = nom ;
		att_prenom = prenom ;
  }

  public String nom()
	{
		return att_nom ;
  }

  public String prenom()
	{
		return att_prenom ;
  }
}
