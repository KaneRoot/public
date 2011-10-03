public class Moyenne
{
	public static void main(String[] args)
	{
		int i, somme = 0;
		int minimum = Integer.parseInt(args[0]);
		int maximum = Integer.parseInt(args[0]);

		for(i = 0 ; i < args.length ; i++)
			somme += Integer.parseInt(args[i]);

		System.out.println("La somme est : " + somme);
		System.out.println("La moyenne est : " + (somme / args.length));
		for(i = 1 ; i < args.length ; i++)
			minimum = min(minimum,Integer.parseInt(args[i]));
		for(i = 1 ; i < args.length ; i++)
			maximum = max(maximum,Integer.parseInt(args[i]));

		System.out.println("Le minimum : " + minimum);
		System.out.println("Le maximum : " + maximum);

	}
	public static int min(int a, int b)
	{
		return (a < b) ? a : b;
	}
	public static int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	public static Integer min(Integer a, Integer b)
	{
		return (a.compareTo(b) <= 0) a : b;
	}
	public static Integer max(Integer a, Integer b)
	{
		return (a.compareTo(b) >= 0) a : b;
	}
}
