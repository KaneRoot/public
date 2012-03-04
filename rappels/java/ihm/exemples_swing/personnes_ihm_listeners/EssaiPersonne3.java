import java.util.Calendar;
import java.util.Date;
import java.util.Arrays;
import java.util.*;

class EssaiPersonne3
{
	public static void main(String[] args)
	{
	Calendar cal = Calendar.getInstance();
		cal.set(1968, Calendar.APRIL, 1);
	Date d0 = cal.getTime();// 01/04/2010
		cal.set(1960, 4, 1);
	Date d1 = cal.getTime();	
		cal.set(1911, Calendar.NOVEMBER, 1);
	Date d2 = cal.getTime();	
	Personne tabp[] = {new Personne("Lampion", "Luc", d0),
					new Personne("Arbogast", "Albert", d0),
					new Personne("Lampion", "Seraphin", d1),
					new Personne("Lampion", "Seraphin", d0),
					new Personne("Lampion", "SERAPHIN", d0),
					new Personne("Dupont", "Denis", d2)};
	ArrayList<Personne> lp = new ArrayList<Personne>();
	
	System.out.println("-----ordre de creation: ");
	for ( Personne p : tabp)  System.out.println(p);
	
	Arrays.sort(tabp);
	System.out.println("\n-----ordre 'naturel':");
	for ( Personne p : tabp)
		{
		System.out.println(p);
		lp.add(p);
		}
		
	System.out.println("\n-----ajouts en fin de liste:");
	lp.add(new Personne("Ambroise", "Albert", d1));
	lp.add(new Personne("AMBROISE", "Berthe", d1));
	System.out.println(lp);
	
	Collections.sort(lp);
	System.out.println("\n-----ordre naturel sur la liste:");
	for ( Personne p : lp) System.out.println(p);
	Collections.sort(lp);
	System.out.println("\n-----ordre date CASE_INSENSITIVE_ORDER:");
	Collections.sort(lp, new CompareDateEtCaseInsensitive());
	for ( Personne p : lp) System.out.println(p);
	System.out.println("\n-----ordre date 'brut':");
	Collections.sort(lp, new CompareDate());
	for ( Personne p : lp) System.out.println(p);
	
	} 
	
}

class CompareDateEtCaseInsensitive implements Comparator<Personne>
{
public int compare(Personne p1 , Personne p2)
	{	
	int res = p1.getDateNaissance().compareTo(p2.getDateNaissance());
	
		if ( res == 0)
			res = String.CASE_INSENSITIVE_ORDER.compare(p1.getNom(),p2.getNom());
		if ( res == 0)
			res = String.CASE_INSENSITIVE_ORDER.compare(p1.getPrenom(),p2.getPrenom());
			
	return res;
	}
}
class CompareDate implements Comparator<Personne>
{
public int compare(Personne p1 , Personne p2)
	{	
	int res = p1.getDateNaissance().compareTo(p2.getDateNaissance());
	
		if ( res == 0)
			res = p1.getNom().compareTo(p2.getNom());
		if ( res == 0)
			res = p1.getPrenom().compareTo(p2.getPrenom());
			
	return res;
	}
}

/*
*/
