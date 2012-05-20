package util;


public class Ellipse extends GeoMorph
{
	private Point2d o_;	// Centre de l'ellipse
	private int a_,b_;	// a_ demi grand axe, b_ demi petit axe
	
	public Ellipse(Point2d o, int a, int b)
	{
		o_ = o;
		a_ = a;
		b_ = b;
	}

	public Ellipse(Point2d f1, Point2d f2, int a, int b)
	{
		this(Point2d.milieu(f1,f2),a,b);
	}

	public Ellipse()
	{
		this(new Point2d(),0,0);
	}	
	
	public int getA(){return a_;}

	public int getB(){return b_;}

	public void setA(int a){a_=a;}
		
	public void setB(int b){b_=b;}

	public Point2d pointBordure(double t)
	{
		return new Point2d((int)((float)o_.getX()+(float)a_*Math.cos(t)+(float)a_/2),
					(int)((float)o_.getY()-b_*Math.sin(t)+(float)b_/2));
	}	
	
	public Point2d getCentre()
	{
		return new Point2d(o_.getX()+a_/2,o_.getY()+b_/2);
	}


}
