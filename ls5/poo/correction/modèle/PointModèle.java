package modèle;
import javax.swing.event.EventListenerList;

public class PointModèle
{
    private int x_;
    private int y_;
    
    private EventListenerList écouteurs_;
    
    public PointModèle(int x, int y)
    {
        x_ = x;
        y_ = y;
        écouteurs_ = new EventListenerList();
    }
    
    public PointModèle()
    {
        this(0, 0);
    }
    
    public int GetX() { return x_; }
    public int GetY() { return y_; }
    public void SetX(int x) { x_ = x; PositionChangée(); }
    public void SetY(int y) { y_ = y; PositionChangée(); }
    public void SetPosition(int x, int y) { x_ = x; y_ = y; PositionChangée(); }
    
    public void AjouterÉcouteurPosition(ChangementPositionListener écouteur)
    {
        écouteurs_.add(ChangementPositionListener.class, écouteur);
    }
    
    public void EnleverÉcouteurPosition(ChangementPositionListener écouteur)
    {
        écouteurs_.remove(ChangementPositionListener.class, écouteur);
    }
    
    private void PositionChangée()
    {
        ChangementPositionListener[] écouteurs = 
                (ChangementPositionListener[])
                écouteurs_.getListeners(ChangementPositionListener.class);
        for (ChangementPositionListener écouteur : écouteurs)
        {
            écouteur.PositionChangée(new ChangementPositionEvent(this, x_, y_));
        }
    }

}
