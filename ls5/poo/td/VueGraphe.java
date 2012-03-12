import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Graphics;

public class VueGraphe extends PointVue implements MouseListener
{
	private int x,y;
	public VueGraphe(PointControleur pc, int x, int y)
	{
		super(pc);
		this.x = x;
		this.y = y;
	}
	@Override
	public void mouseClick(MouseEvent e)
	{
		getControleur().NotifierChangementPosition(e.getX(),e.getY());
	}
	public void Paint(Graphics g)
	{
		super.PaintComponent(g);
		g.drawOval(x,y,10,10);
	}
	public void PositionChangee(ChangementPositionEvent e)
	{
		this.x = e.getNouveauX();
		this.y = e.getNouveauY();
		this.repaint();
	}
}
