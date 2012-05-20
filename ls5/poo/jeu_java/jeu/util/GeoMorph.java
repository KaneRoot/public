package util;


public abstract class GeoMorph
{

	/** 
	*   Renvoie le point du bord de la forme géometrique
	*   selon l'angle t 
	**/
	public abstract Point2d pointBordure(double t);

	/** Renvoie le point réprésentant le centre de la forme géometrique **/
	public abstract Point2d getCentre();

	/** Test si il y a une intersection entre deux forme géometrique **/
	public boolean intersection(GeoMorph g)
	{
		float a = g.getCentre().getY()-this.getCentre().getY(),
		      b = g.getCentre().getX()-this.getCentre().getX();
		
		if (b!=0)
		{
			double d = Math.atan(a/b);
			if (g.getCentre().getY()<this.getCentre().getY())
				d = d+Math.PI;

			Point2d p1 = pointBordure(d),
				p2 = pointBordure(d+Math.PI),
				p3 = g.pointBordure(d+Math.PI);
			
			float d1 = Point2d.distance (this.getCentre(),p1);
			float d2 = Point2d.distance (g.getCentre(),p3);
			
			if (d1>d2)
			{
				return Point2d.distance (this.getCentre(),p3)<=d1;
			}
			else
			{
				return Point2d.distance (g.getCentre(),p1)<=d2;
			}	
		}
		else
			return b==0 && a==0;
	}

	/** 
	*	Test si le point p3 est entre p1 et P2
	*
	* 	@param Point2d p1
	*	@param Point2d p2
	*	@param Point2d p3
	**/
	public boolean intersection(Point2d p1, Point2d p2, Point2d p3)
	{	
		if (p1.getX()>=p2.getX() && p1.getY()>=p2.getY())
			return (p1.getX()>=p3.getX() && p2.getX()<=p3.getX() &&
				p1.getY()>=p3.getY() && p2.getY()<=p3.getY());
		else if (p1.getX()>=p2.getX() && p1.getY()<=p2.getY())
			return (p1.getX()>=p3.getX() && p2.getX()<=p3.getX() &&
				p1.getY()<=p3.getY() && p2.getY()>=p3.getY());
		else if (p1.getX()<=p2.getX() && p1.getY()<=p2.getY())
			return (p1.getX()<=p3.getX() && p2.getX()>=p3.getX() &&
				p1.getY()<=p3.getY() && p2.getY()>=p3.getY());
		else
			return (p1.getX()<=p3.getX() && p2.getX()>=p3.getX() &&
				p1.getY()>=p3.getY() && p2.getY()<=p3.getY());
	}

}
