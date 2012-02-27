public class SexDec
{
	private double heures;
	public SexDec(int heures, int minutes, int secondes)
	{
		this.heures = heures+(minutes/60.)+(secondes/3600.);
	}
	public SexDec(double heures)
	{
		this.heures = heures;
	}
	public double getDec()
	{
		return this.heures;
	}
	public int getH()
	{
		return (int) this.heures;
	}
	public int getM()
	{
		return (int) (this.heures * 60)%60;
	}
	public int getS()
	{
		return (int) (this.heures*3600)%60;
	}
}
