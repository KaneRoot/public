import java.util.Date;
class Utilisateur extends Personne
{
	private String login;
	private String email;
	
	public Utilisateur(String n,String p, Date d)
	{
		super(n,p,d);
		this.login=getDefaultLogin();
		this.email=getLocalEmail();
	}
	
	private static String initCap(String str)
	{
		String res;
		if(str.length()>0)
		{
			String plettre=str.substring(0,1);
			plettre=plettre.toUpperCase();
			
			if(str.length()>1)
			{
				String reste=str.substring(1);
				reste=reste.toLowerCase();
				res=plettre+reste;
			}
			else
			{
				res=plettre;
			}
		}
		else
		{
			res=str;
		}
		return res;
	}
	@Override
	public String getNom()
	{
		String nom=super.getNom();
		return nom.toUpperCase();
	}
	@Override
	public String getPrenom()
	{
		String prenom=super.getPrenom();
		return initCap(prenom);
	}
	public String getLogin()
	{
		return this.login;
	}
	public void setLogin(String s)
	{
		this.login=s;
	}
	public String getEmail()
	{
		return this.email;
	}
	public void setEmail(String s)
	{
		this.email=s;
	}
	public String getDefaultLogin()
	{
		return getPrenom().toLowerCase()+"."+getNom().toLowerCase();
	}
	public String getLocalEmail()
	{
		return getDefaultLogin()+"@"+Utilisateur.ADRESSE_LOCALE;
	}
	@Override
	public String toString()
	{
		String res=super.toString();
		res=res+" "+this.login+" "+this.email;
		return res;
	}
	private static final String ADRESSE_LOCALE = "etu.unistra.fr";
}
