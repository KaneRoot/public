package paquetMain;

import paquetSuite.*;
import paquetException.*;

public class Test
{
	public static void main(String[] args)
	{
		Suite s1 = new SuiteArithm(10, 5);
		Suite s2 = new SuiteGeom(5, 3);

		try
		{
			System.out.println("10 5 arithm valeur au rang 5 = " + s1.valeurAuRangN(5));
			System.out.println("10 5 arithm somme au rang 3 = " + s1.sommeAuRangN(3));
			System.out.println("5 3 geom valeur au rang 2 = " + s2.valeurAuRangN(2));
			System.out.println("5 3 geom somme au rang 2 = " + s2.sommeAuRangN(-1));
		}
		catch(SuiteException x)
		{
			System.out.println("Erreur : " + x.getMessage());
		}
	}
}
