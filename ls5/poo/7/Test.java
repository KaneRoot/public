import java.util.StringTokenizer;
import java.util.ArrayList;

public class Test
{
	public static void main(String[] args)
	{
		StringTokenizer st = new StringTokenizer(args[0]);
		List<Symbole> l = new ArrayList<Symbole>();

		while(st.hasNext())
		{
			Symbole s = new Symbole(st.next());
			l.add(s);
		}
		System.out.prinln(aToN(l).calcul());
	}
}
