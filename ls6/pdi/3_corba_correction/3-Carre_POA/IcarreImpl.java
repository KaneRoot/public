import org.omg.CORBA.* ;

public class IcarreImpl
  extends IcarrePOA
{
  public int carre (int source)
  {
    System.out.println( "carre : requete recue pour le nombre : " + source ) ;
    return source * source ;
  }
}
