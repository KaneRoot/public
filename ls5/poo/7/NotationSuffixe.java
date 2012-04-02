import java.util.ArrayList;

public class NotationSuffixe
{
	public ArrayList<Symbole> symboles;

	public NotationSuffixe()
	{
		this.symboles = new ArrayList<Symbole>(20);

		Symbole a;
		a = new Symbole("1"); this.symboles.add(a);
		a = new Symbole("2"); this.symboles.add(a);
		a = new Symbole("7"); this.symboles.add(a);
		a = new Symbole("8"); this.symboles.add(a);
		a = new Symbole("+"); this.symboles.add(a);
		a = new Symbole("3"); this.symboles.add(a);
		a = new Symbole("4"); this.symboles.add(a);
		a = new Symbole("*"); this.symboles.add(a);
		a = new Symbole("/"); this.symboles.add(a);
		a = new Symbole("*"); this.symboles.add(a);
		a = new Symbole("+"); this.symboles.add(a);
		a = new Symbole("2"); this.symboles.add(a);
		a = new Symbole("+"); this.symboles.add(a);
	}

	public Noeud atoN(ArrayList LS)
	{
		ArrayList<Noeud> LN = new ArrayList<Noeud>();
		Iterator it = LS.iterator();

		while(it.hasNext())
		{
			Symbole s = it.next();
			if(s.estNombre())
			{
				LN.add(new Noeud(s, null, null));
			}
			else
			{
				Noeud n, m;
				n = LN.get(LN.length - 2);
				m = LN.get(LN.length - 1);
				LN.remove(LN.length - 1);
				LN.remove(LN.length - 1);
				LN.add(new Noeud(s, n, m));
			}
		}
		return LN.get(0);
	}
}
