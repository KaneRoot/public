import java.util.ArrayList;
import java.util.Iterator;

public class NotationSuffixe
{
	public ArrayList<Symbole> symboles;

	public NotationSuffixe()
	{
		this.symboles = new ArrayList<Symbole>(20);
	}

	public Noeud aToN(ArrayList LS)
	{
		ArrayList<Noeud> LN = new ArrayList<Noeud>();
		Iterator it = LS.iterator();

		while(it.hasNext())
		{
			Symbole s = (Symbole) it.next();
			if(s.estNombre())
			{
				LN.add(new Noeud(s, null, null));
			}
			else
			{
				Noeud n, m;
				n = LN.get(LN.size() - 2);
				m = LN.get(LN.size() - 1);
				LN.remove(LN.size() - 1);
				LN.remove(LN.size() - 1);
				LN.add(new Noeud(s, n, m));
			}
		}
		return LN.get(0);
	}
}
