import javax.swing.event.EventListenerList;

public class PointModele
{
	private int x, y;
	private EventListenerList listenerList = new EventListenerList();

	public PointModele(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	public int getX()
	{
		return this.x;
	}
	public int getY()
	{
		return this.y;
	}
	public void set(int x, int y)
	{
		fireChangementPosition();
	}
	public void addChangementPositionListener(ChangementPositionListener l)
	{
		this.listenerList.add(ChangementPositionListener.class, l);
	}
	public void removeChangementPositionListener(ChangementPositionListener l)
	{
		this.listenerList.remove(ChangementPositionListener.class, l);
	}
	protected void fireChangementPosition()
	{
		/* Méthode qui ne marche pas
		Object[] listeners = listenerList.getListenerList(ChangementPositionListener.class);
		for(int i = listeners.length - 1 ; i >= 0 ; i--)
			listeners[i].PositionChangee(new ChangementPositionEvent(this, this.x, this.y));
		*/

		Object[] listeners = listenerList.getListenerList();
		for(int i = listeners.length - 2 ; i >= 0 ; i -= 2)
			if(listeners[i] == ChangementPositionListener.class)
				((ChangementPositionListener) listeners[i+1]).PositionChangee(new ChangementPositionEvent(this, this.x, this.y));
	}
}
