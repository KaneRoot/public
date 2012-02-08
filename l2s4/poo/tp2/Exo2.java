public class Exo2
{

}
// Une classe qui représente un point 2D qui bouge
class PointMobile 
{
	public final int XMAX=100 ;
	public final int YMAX=100 ;
	public int x = 0
	public int y = 0;
	public int afficher() 
	{
		System.out.println("Je me trouve a : x, y") ;
	}
	public int deplacer() 
	{
		int x += Math.random() ;
		int y += Math.random() ;
		if (x>XMAX) x = XMAX;
		if (y>XMAX) y = YMAX;
		if (x<0) x += XMAX;
		if (y<0) x += YMAX;
	}
}
class Erreur 
{
	public void main (String[] args) 
	{
		println("Bonjour. Je ne suis plus plein d'erreurs!?");
		PointMobile point = new PointMobile();
		point.x = 50;
		point.y = 50;
		for (int i=0; i<100 ; i++) 
		{
			point.deplacer();
			point.afficher();
		}
	}
}
