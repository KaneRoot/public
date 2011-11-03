import java.io.*;
public class TestPile
{
	public static void main(String[] argv)
	{
		Expression exp;
		String op = "";
		BufferedReader br;
		br = new BufferedReader(new InputStreamReader(System.in));
		try
		{
			System.out.println("Entrez l'expression : ");
			op = br.readLine();
			exp = new Expression(op);
			System.out.println("Ce qui vaut : " + exp.evalue());
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.exit(1);
		}
	}
}
