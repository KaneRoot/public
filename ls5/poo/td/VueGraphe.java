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
	public void mouseClicked(MouseEvent e)
	{
		getControleur().NotifierChangementPosition(e.getX(),e.getY());
	}
	public void Paint(Graphics g)
	{
		paintComponent(g);
		g.drawOval(x,y,10,10);
	}
	@Override
	public void PositionChangee(ChangementPositionEvent e)
	{
		this.x = e.getNouveauX();
		this.y = e.getNouveauY();
		this.repaint();
	}

    @Override
    public void mousePressed(MouseEvent e) {}

    @Override
    public void mouseReleased(MouseEvent e) {}

    @Override
    public void mouseEntered(MouseEvent e) {}

    @Override
    public void mouseExited(MouseEvent e) {}
}
