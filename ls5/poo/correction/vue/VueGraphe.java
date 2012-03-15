package vue;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.JPanel;

public class VueGraphe extends PointVue implements MouseListener
{
    private int x_;
    private int y_;
    JPanel panneau_;
    
    public VueGraphe(contrôleur.PointContrôleur contrôleur, int x, int y)
    {
        super(contrôleur);
        x_ = x;
        y_ = y;
        panneau_ = new JPanel()
            {
                @Override
                public void paint(Graphics g)
                {
                    g.setColor(Color.WHITE);
                    g.fillRect(0, 0, 1000, 1000);
                    g.setColor(Color.BLUE);
                    g.drawLine(0, 500, 1000, 500);
                    g.drawLine(500, 0, 500, 1000);
                    g.setColor(Color.BLACK);   
                    for (int x = -5; x <= 5; x++)
                    {
                        if (x != 0)
                        {
                            g.drawLine(x*100+500, 0, x*100+500, 1000);
                            g.drawLine(0, x*100+500, 1000, x*100+500);
                        }
                    }
                    g.setColor(Color.RED);
                    g.fillOval(x_*100+475, y_*100+475, 50, 50);   
                }
             };
        setContentPane(panneau_);
        panneau_.addMouseListener(this);
        pack();
        setSize(1000, 1000);
        
    }


    @Override
    public void PositionChangée(modèle.ChangementPositionEvent event)
    {
        x_ = event.GetNouveauX();
        y_ = event.GetNouveauY();
        panneau_.repaint();
    }

    @Override
    public void mouseClicked(MouseEvent e)
    {
        int x = (e.getX()-500)/100;
        int y = (e.getY()-500)/100;
        System.out.println(x + " " + y);
        GetContrôleur().NotifierChangementPosition(x, y);
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