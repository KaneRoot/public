package vue;
import java.awt.GridLayout;
import javax.swing.JPanel;
import javax.swing.JScrollBar;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class VueSlider extends PointVue implements ChangeListener
{
    private JScrollBar scrollX_;
    private JScrollBar scrollY_;
    
    public VueSlider(contrôleur.PointContrôleur contrôleur, int x, int y)
    {
        super(contrôleur);
        scrollX_ = new JScrollBar(JScrollBar.HORIZONTAL, 0, 0, -5, 5);
        scrollY_ = new JScrollBar(JScrollBar.HORIZONTAL, 0, 0, -5, 5);
        scrollX_.getModel().addChangeListener(this);
        scrollY_.getModel().addChangeListener(this);
        JPanel content = new JPanel();
        GridLayout grid = new GridLayout(2,1);
        content.setLayout(grid);
        content.add(scrollX_);
        content.add(scrollY_);
        setContentPane(content);
        pack();
        setSize(200, 200);
    }


    @Override
    public void PositionChangée(modèle.ChangementPositionEvent event)
    {
        scrollX_.setValue(event.GetNouveauX());
        scrollY_.setValue(event.GetNouveauY());
    }

    @Override
    public void stateChanged(ChangeEvent e)
    {
        GetContrôleur().NotifierChangementPosition(scrollX_.getValue(), scrollY_.getValue());
    }


}
