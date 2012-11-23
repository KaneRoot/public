import org.omg.CORBA.* ;

public class IcarreImpl extends _IcarreImplBase
{
	public void carre (LongHolder source, LongHolder resultat)
	{
		System.out.println( "carre : requete recue pour le nombre : " + source ) ;
		resultat.value = source.value * source.value ;
	}
}
