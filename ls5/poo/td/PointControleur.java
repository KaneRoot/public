public class PointControleur
{
	private PointModele pm;
	public PointControleur(PointModele pm)
	{
		this.pm = pm;
	}
	public void AfficherVue()
	{
		VueGraphe vg = new VueGraphe(this, this.pm.getX(), this.pm.getY());
		VueSlider vs = new VueSlider(this, this.pm.getX(), this.pm.getY());
		this.pm.addChangementPositionListener(vg);
		this.pm.addChangementPositionListener(vs);
		vg.setVisible(true);
		vs.setVisible(true);
	}
}
