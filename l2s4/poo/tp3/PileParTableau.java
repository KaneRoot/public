import java.lang.Integer;
public class PileParTableau
{
	public Integer tab[];
	public int indice;
	public PileParTableau(int taille)
	{
		this.indice = 0;
		this.tab = new Integer[taille];
	}
	public boolean pileVide()
	{
		return (this.indice == 0);
	}
	public boolean pilePleine()
	{
		return (this.tab.length == this.indice);
	}
	public Integer depiler()
	{
		if(! this.pileVide())
		{
			this.indice--;
			return this.tab[this.indice];
		}
		return (Integer) null;
	}
	public void empiler(Integer i)
	{
		if(! this.pilePleine())
		{
			this.tab[this.indice] = i;
			this.indice++;
		}
	}
}
