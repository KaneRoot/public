package util;

public class Bounding
{
	private GeoMorph forme_;

	public Bounding(GeoMorph forme)
	{
		forme_ = forme;
	}

	public GeoMorph getForme()	
	{
		return forme_;
	}	

	public boolean estEnCollision(Bounding b)
	{
		return forme_.intersection(b.getForme());
	}
}
