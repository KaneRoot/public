package util;


public class Rectangle extends GeoMorph
{

	private Point2d o_; // Centre du rectangle 
	private int a_,b_;  // a_ largeur, b_ hauteur

	public Rectangle(Point2d o, int a, int b)
	{
		o_ = o;
		a_ = a;
		b_ = b; 
	}
	
	public Rectangle()
	{
		this(new Point2d(),0,0);
	}

	public Point2d pointBordure(double t)	
	{
		if (t>0 && t<=Math.PI/2)
			return new Point2d(getCentre().getX()+(a_/2),
					getCentre().getY()+(b_/2));
		else if (t>Math.PI/2 && t<=Math.PI)
			return new Point2d(getCentre().getX()-(a_/2),
					getCentre().getY()+(b_/2));
		else if (t>Math.PI && t<=3*Math.PI/2)
			return new Point2d(getCentre().getX()-(a_/2),
					getCentre().getY()-(b_/2));
		else
			return new Point2d(getCentre().getX()+(a_/2),
					getCentre().getY()-(b_/2));
	}

	public Point2d getCentre()
	{
		return new Point2d(o_.getX()+a_/2,o_.getY()-b_/2);
	}
}
