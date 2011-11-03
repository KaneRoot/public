public class TSexDec 
{
	public static void main (String args[]) 
	{
		SexDec h1 = new SexDec(4.51) ;
		System.out.println("h1 decimal = " + h1.getDec() + " Sexa = " + h1.getH() + ":" + h1.getM() + ":" + h1.getS()) ;
		SexDec h2 = new SexDec(2, 32, 15) ;
		System.out.println("h2 decimal = " + h2.getDec() + " Sexa = " + h2.getH() + ":" + h2.getM() + ":" + h2.getS());
	}
}
