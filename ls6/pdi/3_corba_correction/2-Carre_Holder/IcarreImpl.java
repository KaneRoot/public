import org.omg.CORBA.* ;

public class IcarreImpl
	extends _IcarreImplBase
{
	public void carre (int source, IntHolder resultat)
	{
		System.out.println( "carre : requete recue pour le nombre : " + source ) ;
		resultat.value = source*source ;
 	}
}
