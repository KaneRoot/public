import java.io.*;

public class Calculatrice
{

	public static void main(String[] args)
	{
		/*
		int op1 = Integer.parseInt(args[0]);
		int op2 = Integer.parseInt(args[2]);
		calcul(op1,op2,args[1].charAt(0));
		*/
		interactif();
	}
	public static void calcul(int op1, int op2 , char c)
	{
		switch(c)
		{
			case '+' :
				System.out.println("Le résultat de la somme est : " + op1 + " + " + op2 + " = " + (op1+op2));
				break;
			case '-' :
				System.out.println("Le résultat de la soustraction est : " + op1 + " - " + op2 + " = " + (op1-op2));
				break;
			case '/' :
				System.out.println("Le résultat de la division est : " + op1 + " / " + op2 + " = " + (op1/op2));
				break;
			case '*' :
				System.out.println("Le résultat de la multiplcation est : " + op1 + " * " + op2 + " = " + (op1*op2));
				break;
			case '%' :
				System.out.println("Le résultat du modulo est : " + op1 + " % " + op2 + " = " + (op1%op2));
				break;
			case '^' :
				System.out.println("Le résultat de la puissance est : " + op1 + " ^ " + op2 + " = " + (int)Math.pow(op1,op2));
				break;
			default :
				System.out.println("Opérateur inconnu");
		}
	}
	public static void interactif()
	{
		int op1 = 0 ,op2 = 0;
		char c = '+' ;
		BufferedReader br;
		br = new BufferedReader(new InputStreamReader(System.in));
		try
		{
			System.out.println("Entrez la première opérande : ");
			op1 = Integer.parseInt(br.readLine());
			System.out.println("Entrez l'opération : ");
			c = br.readLine().charAt(0);
			System.out.println("Entrez la deuxième opérande : ");
			op2 = Integer.parseInt(br.readLine());
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
			System.exit(1);
		}

		calcul(op1,op2,c);
		System.out.println("Fin du programme");

	}
}
