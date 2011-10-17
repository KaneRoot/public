import java.io.*;

public class SomeTests
{
	public static void main(String[] args)
	{
		/*
		while(l())
			System.out.println("On continue");
		while(villeschaines())
			System.out.println("On continue");
		*/
		dernier_exo();

	}
	public static void tests(String s1, String s2)
	{
		System.out.println("Résultat de s1.length() : " + s1.length());
		System.out.println("Résultat de s1 == s2 : " + (s1 == s2));
		System.out.println("Résultat de s1.equals(s2) : " + s1.equals(s2));
		System.out.println("Résultat de s1.compareTo(s2) : " + s1.compareTo(s2));
		System.out.println("Résultat de s1.compareToIgnoreCase(s2) : " + s1.compareToIgnoreCase(s2));
		if(s1.charAt(0) == s2.charAt(0))
			System.out.println("Les 2 chaînes commencent par la même lettre : " + s1.charAt(0));
		else
			System.out.println("Les 2 chaînes ne commencent pas par la même lettre : " + s1.charAt(0) + " et " + s2.charAt(0));
		if(s1.startsWith(s2))
			System.out.println("s1 commence par s2");
		else
			System.out.println("s1 ne commence pas par s2");
		if(s1.endsWith(s2))
			System.out.println("s1 se termine par s2");
		else
			System.out.println("s1 ne se termine pas par s2");
		if(s1.contains(s2))
			System.out.println("s1 contient s2");
		else
			System.out.println("s1 ne contient pas s2");
		System.out.println("concaténation s1s2 = : " + s1 + s2);
		System.out.println("Remplacement de o par O dans s1 : " + s1.replace('o','O'));
		if(s1.contains(s2))
		{
			System.out.println("s1 privé de s2 : " + s1.replace(s2,"")); //
			System.out.println("s1 privé de s2 : " + s1.substring(0,s1.indexOf(s2)) + s1.substring(s1.indexOf(s2)+s2.length()));
		}
		else
			System.out.println("s1 ne contient pas s2 : " + s1);

		System.out.println("_________________________");
	}
	public static boolean l()
	{
		boolean b = true;
		String s1="",s2="";
		BufferedReader br;
		br = new BufferedReader(new InputStreamReader(System.in));
		try
		{
			System.out.println("Entrez une chaîne : ");
			s1 = br.readLine();
			System.out.println("Entrez une seconde chaîne : ");
			s2 = br.readLine();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.exit(1);
		}
		tests(s1,s2);
		if(s2.compareToIgnoreCase("exit") == 0)
			b = false;
		return b;
	}
	public static boolean villeschaines()
	{
		String s = lire();

		System.out.println("Ville en majuscule : " + s.toUpperCase());
		s = s.trim();
		System.out.println("On va trim tout ça : " + s);
		
		String[] strs = s.split(" ");
		for(int i = 0; i < strs.length ; i++)
			System.out.println("Index : " + i + " : " + strs[i]);
		return true;
	}
	public static String lire()
	{
		String s="";
		BufferedReader br;
		br = new BufferedReader(new InputStreamReader(System.in));
		try
		{
			System.out.println("Entrez une chaîne : ");
			s = br.readLine();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.exit(1);
		}
		if(s.compareToIgnoreCase("exit") == 0)
			System.exit(0);
		return s;
	}
	public static void dernier_exo()
	{
		String s = "qqch";
		StringBuffer s1 = new StringBuffer();
		StringBuffer s2 = new StringBuffer(0);
		StringBuffer s3 = new StringBuffer("coucou");
		s1.append("coucou");

		System.out.println(s1);
		System.out.println(		s2.append("coucou"));
		System.out.println(		s3.append("coucou2"));

		System.out.println("String : s.toUpperCase() : " + s.toUpperCase());
		System.out.println("s : " + s);
	}
}
