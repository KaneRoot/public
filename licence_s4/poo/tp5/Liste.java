public class Liste
{
	private Noeud debut;
	private Noeud dernier;
	public Liste(String s)
	{
		this.debut = new Noeud(s);
		this.dernier = this.debut;
	}
	public Liste()
	{
		this.debut = null;
		this.dernier = null;
	}
	public void insererDebut(String s)
	{
		Noeud tmp = new Noeud(this.debut, s);
		this.debut = tmp;
		tmp.setPrecedent(this.debut);
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
	public void insererFin(String s)
	{
		if(this.dernier == null)
		{
			this.dernier = new Noeud(s);
		}
		this.dernier.setSuivant(new Noeud(s));
		this.dernier.getSuivant().setPrecedent(this.dernier);
		this.dernier = this.dernier.getSuivant();

	}
	public void insererPositionDonnee(String s, int pos)
	{
		Noeud n = new Noeud(s);
		Noeud tmp = this.debut;
		Noeud tmp2 = this.debut;
		if(pos == 0 || this.debut == null)
		{
			this.insererDebut(s);
			return;
		}
		if(pos > this.taille())
		{
			this.insererFin(s);
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
		n.setPrecedent(tmp2);
		tmp.setPrecedent(n);
	}
}

class Noeud
{
	private String donnee;
	private Noeud suivant;
	private Noeud precedent;
	public Noeud(Noeud s, String donnee)
	{
		this.suivant = s;
		this.donnee = donnee;
	}
	public Noeud(String donnee)
	{
		this(null,donnee);
	}
	public Noeud getPrecedent()
	{
		return this.precedent;
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
	public void setPrecedent(Noeud n)
	{
		this.precedent = n;
	}
	public void setSuivant(Noeud n)
	{
		this.suivant = n;
	}
	@Override
	public String toString()
	{
		return "Donnée : " + this.donnee;
	}
}
