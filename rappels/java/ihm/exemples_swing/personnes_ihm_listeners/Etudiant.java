import java.lang.String;
import java.util.Date;

public class Etudiant extends Utilisateur
{
	private int groupe;
	private int promo;
	
	public Etudiant(String n, String p, Date d)
	{
		super(n,p,d);
	}
	public Etudiant(String n, String p, Date d, int grp, int prom)
	{
		super(n,p,d);
		this.groupe = grp;
		this.promo = prom;
	}
	public int getGroupe()
	{
		return this.groupe;
	}
	public int getPromo()
	{
		return this.promo;
	}
	public void setGroupe(int g)
	{
		this.groupe = g;
	}
	public void setPromo(int p)
	{
		this.promo = p;
	}
	public String toString()
	{
		return super.toString()+ " " + this.getPromo() + " " + this.getGroupe();
	}
}
