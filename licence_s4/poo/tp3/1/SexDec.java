public class SexDec
{
	private int heures;
	private int minutes;
	private int secondes;
	public SexDec(int heures, int minutes, int secondes)
	{
		this.heures = heures;
		this.minutes = minutes;
		this.secondes = secondes;

	}
	public SexDec(double heures)
	{
		this((int) heures, (int)((heures%1)*60), (int)((heures*3600)%60));
	}
	public double getDec()
	{
		return (double) this.heures + this.minutes/60. + this.secondes/3600.;
	}
	public int getH()
	{
		return this.heures;
	}
	public int getM()
	{
		return this.minutes;
	}
	public int getS()
	{
		return this.secondes;
	}
}
