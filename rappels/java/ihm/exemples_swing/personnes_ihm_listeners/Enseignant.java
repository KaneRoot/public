import java.lang.String;
import java.util.Date;

public class Enseignant extends Utilisateur
{
	private int tel;
	private int bureau;
	
	public Enseignant(String n, String p, Date d)
	{
		super(n,p,d);
	}
	public Enseignant(String n , String p, Date d, int noTel, int noBureau)
	{
		super(n,p,d);
		this.bureau = noBureau;
		this.tel = noTel;
	}
	public int getBureau()
	{
		return this.bureau;
	}
	public void setBureau(int noBureau)
	{
		this.bureau = noBureau;
	}
	public int getTel()
	{
		return this.tel;
	}
	public void setTel(int noTel)
	{
		this.tel = noTel;
	}
	public String toString()
	{
		return super.toString() + " " + this.getTel() + " " + this.getBureau();
	}
}
