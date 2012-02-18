// La classe Binome est comme demandée avec en plus des getter et de setter
// car les attributs a_, b_, c_ et dis_ sont privés (donc non disponibles dans les classes filles)
public class Binome
{
	private double a_,b_,c_,dis_;
	protected Binome(double a, double b, double c, double dis)
	{
		a_ = a; b_ = b; c_ = c; dis_ = dis;
	}
	public void CalculeRacines()
	{
		System.out.println("Calcul racines : erreur (classe Binome)");
	}
	public int NbRacines()
	{
		System.out.println("Calcul NbRacines : erreur (classe Binome)");
		return 0;
	}
	public double ValeurRacine(int i)
	{
		System.out.println("Calcul ValeurRacine : erreur (classe Binome)");
		return 0.0;
	}

	// SET
	public void setA(double a)
	{
		this.a_ = a;
	}
	public void setB(double b)
	{
		this.b_ = b;
	}
	public void setC(double c)
	{
		this.c_ = c;
	}
	public void setDis(double dis)
	{
		this.dis_ = dis;
	}

	// GET
	public double getA()
	{
		return this.a_;
	}
	public double getB()
	{
		return this.b_;
	}
	public double getC()
	{
		return this.c_;
	}
	public double getDis()
	{
		return this.dis_;
	}
}
