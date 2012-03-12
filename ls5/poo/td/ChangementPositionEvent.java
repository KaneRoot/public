import java.util.EventObject;

public class ChangementPositionEvent extends EventObject
{
	private int nouveauX_, nouveauY_;
	public ChangementPositionEvent(Object source, int nouvX, int nouvY)
	{
		super(source);
		this.nouveauX_ = nouvX;
		this.nouveauY_ = nouvY;
	}
	public int getNouveauX() { return this.nouveauX_; }
	public int getNouveauY() { return this.nouveauY_; }
}
