public class Moyenne
{
	public static void main(String[] args)
	{
		int i, somme = 0;
		for(i = 0 ; i < args.length ; i++)
			somme += Integer.parseInt(args[i]);

		System.out.println("La somme est : " + somme);
		System.out.println("La moyenne est : " + (somme / args.length));
	}
}
