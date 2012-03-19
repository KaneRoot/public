package contrôleur;

public class PointContrôleur
{
    private vue.PointVue vueGraphe_ = null;
    private vue.PointVue vueSlider_ = null;
    
    private modèle.PointModèle pointMod_ = null;
    
    public PointContrôleur(modèle.PointModèle pointMod)
    {
        pointMod_ = pointMod;
        int x = pointMod.GetX();
        int y = pointMod.GetY();
        vueGraphe_ = new vue.VueGraphe(this, x, y);
        vueSlider_ = new vue.VueSlider(this, x, y);
        pointMod_.AjouterÉcouteurPosition(vueSlider_);
        pointMod_.AjouterÉcouteurPosition(vueGraphe_);
    }
    
    public void AfficherVues()
    {
        vueGraphe_.setVisible(true);
        vueSlider_.setVisible(true);
    }
    
    public void NotifierChangementPosition(int x, int y)
    {
        pointMod_.SetPosition(x, y);
    }

}
