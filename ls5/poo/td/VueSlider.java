import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import javax.swing.JScrollBar;
import java.awt.GridLayout;
import javax.swing.JPanel;

public class VueSlider extends PointVue implements ChangeListener
{
	private int x, y;
	private JScrollBar sx, sy;

	public VueSlider(PointControleur pc, int x, int y)
	{
		super(pc);
		this.x = x;
		this.y = y;

		this.sx = new JScrollBar();
		this.sy = new JScrollBar();
		this.sx.addChangeListener(this);
		this.sy.addChangeListener(this);

		JPanel jp = new JPanel();
		jp.setLayout(new GridLayout(2,1));
		jp.add(sx);
		jp.add(sy);

		this.add(jp);
	}
	public void stateChanged(ChangeEvent e)
	{
		getControleur().NotifierChangementPosition(sx.getValue(), sy.getValue());
	}
	public void positionChangee(ChangementPositionEvent e)
	{
		sx.setValue(e.getNouveauX());
		sy.setValue(e.getNouveauY());
	}
}
