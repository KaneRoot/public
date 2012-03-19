import java.util.ArrayList;

public class Chemin
{
	ArrayList<Case> lCases;
	public Chemin(ArrayList<Case> chemin)
	{
		this.lCases = chemin;
	}
	public Chemin()
	{
		this(new ArrayList<Case>());
	}
	public boolean faitPartieDuChemin(Case c)
	{
		return this.lCases.contains(c);
	}
	public void ajouterCase(Case c)
	{
		this.lCases.add(c);
	}
	public void enleverCase(Case c)
	{
		this.lCases.remove(c);
	}
}
