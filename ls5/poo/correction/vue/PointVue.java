package vue;
import javax.swing.JFrame;

public abstract class PointVue extends JFrame implements modèle.ChangementPositionListener
{
    private contrôleur.PointContrôleur contrôleur_ = null;
    
    public PointVue(contrôleur.PointContrôleur contrôleur)
    {
        super();
        contrôleur_ = contrôleur;
    }
    
    public final contrôleur.PointContrôleur GetContrôleur() { return contrôleur_; }
    

}
