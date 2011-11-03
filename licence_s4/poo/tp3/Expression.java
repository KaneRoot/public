public class Expression
{
	public String line;
	public Expression(String line)
	{
		this.line = line;
	}
	public Integer evalue()
	{
		int retour, i = 0;
		String tmp[] = this.line.split(" ");
		PileParTableau p = new PileParTableau(tmp.length);
		while(i != tmp.length)
		{
			if(Expression.operateur(tmp[i]))
			{
				p.empiler(Expression.calcul(p.depiler(),p.depiler(),tmp[i]));
				System.out.println("Évaluation");
			}
			else
			{
				System.out.println("Empilement");
				p.empiler(new Integer(tmp[i]));
			}
			i++;
		}
		return p.depiler();
	}
	public static boolean operateur(String s)
	{
		boolean b = false;
		try
		{
			Integer.valueOf(s);
		}
		catch(NumberFormatException e)
		{
			System.out.println("EXCEPTION");
			b = true;
		}
		return b;
	}
	public static Integer calcul(Integer a, Integer b, String op)
	{
		if(op.charAt(1) == '+')
			return new Integer(a+b);
		if(op.charAt(1) == '-')
			return new Integer(a-b);
		if(op.charAt(1) == '/')
			return new Integer(a/b);
		if(op.charAt(1) == '*')
			return new Integer(a*b);
		return null;
	}
}
