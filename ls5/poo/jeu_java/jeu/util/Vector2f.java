package util;


public class Vector2f 
{
	private float i_,j_;
	
	public Vector2f (float i, float j)
	{
		setI(i);
		setJ(j);
	}
	
	public Vector2f ()
	{
		this (0f,0f);
	}

	public void setI(float i) 
	{
		this.i_ = i;
	}

	public float getI() 
	{
		return i_;
	}

	public void setJ(float j)
	{
		this.j_ = j;
	}

	public float getJ() 
	{
		return j_;
	}
	
	public float norme()
	{
		return (float)Math.sqrt(Math.pow((double)i_,2)+Math.pow((double)j_,2));
	} 
	
	public void add(Vector2f v)
	{
		i_ += v.getI();
		j_ += v.getJ();
	}

	public void multScalaire(float scal)
	{
		i_ = i_*scal;
		j_ = j_*scal;
	}

	public void mult(Vector2f v)
	{
		i_ = i_*v.getI();
		j_ = j_*v.getJ();
	}
	
	public boolean equals(Vector2f v)
	{
		return (i_ == v.getI()) && (j_ == v.getJ());
	}
	
	public boolean isZero()
	{
		return (norme()==0);
	}
	
}
