public class Liste
{
	private Noeud debut;
	public Liste(String s)
	{
		this.debut = new Noeud(s);
	}
	public Liste()
	{
		this.debut = null;
	}
	public void insererDebut(String s)
	{
		Noeud tmp = new Noeud(this.debut, s);
		this.debut = tmp;
	}
	@Override
	public String toString()
	{
		String s = "";
		Noeud tmp = this.debut;
		while(tmp != null)
		{
			s += tmp.toString() + "\n";
			tmp = tmp.getSuivant();
		}
		return s;
	}
	public int taille()
	{
		int t = 0;
		Noeud tmp = this.debut;
		while(tmp != null)
		{
			t++;
			tmp = tmp.getSuivant();
		}
		return t;
	}
	public void insererPositionDonnee(String s, int pos)
	{
		Noeud n = new Noeud(s);
		Noeud tmp = this.debut;
		Noeud tmp2 = this.debut;
		if(pos == 0)
		{
			n.setSuivant(this.debut);
			this.debut = n;
			return;
		}
		if(this.debut == null)
		{
			this.debut = n;
			return;
		}
		while(tmp != null && (pos-1) > 0)
		{
			tmp2 = tmp;
			tmp = tmp.getSuivant();
			pos--;
		}
		// On se trouve à la position qu'on veut insérer
		tmp2.setSuivant(n);
		n.setSuivant(tmp);
	}
}

class Noeud
{
	private String donnee;
	private Noeud suivant;
	public Noeud(Noeud s, String donnee)
	{
		this.suivant = s;
		this.donnee = donnee;
	}
	public Noeud(String donnee)
	{
		this(null,donnee);
	}
	public Noeud getSuivant()
	{
		return this.suivant;
	}
	public String getDonnee()
	{
		return this.donnee;
	}
	public void setDonnee(String s)
	{
		this.donnee = s;
	}
	public void setSuivant(Noeud s)
	{
		this.suivant = s;
	}
	@Override
	public String toString()
	{
		return "Donnée : " + this.donnee;
	}
}
