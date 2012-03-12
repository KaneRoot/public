import javax.swing.JFrame;

public abstract class PointVue extends JFrame implements ChangementPositionListener
{
	protected PointControleur pc;
	public PointVue(PointControleur pc)
	{
		this.pc = pc;
	}
	public PointControleur getControleur()
	{
		return this.pc;
	}
}
