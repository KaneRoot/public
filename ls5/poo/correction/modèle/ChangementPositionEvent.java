package modèle;
import java.util.EventObject;

public class ChangementPositionEvent extends EventObject
{
    private int nouveauX_;
    private int nouveauY_;
    
    public ChangementPositionEvent(Object source, int nouvX, int nouvY)
    {
        super(source);
        nouveauX_ = nouvX;
        nouveauY_ = nouvY;
    }
    
    public int GetNouveauX() { return nouveauX_; }
    public int GetNouveauY() { return nouveauY_; }
	
}