package vue;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JPanel;

import controleur.ControlerMap;
import modele.event.*;
import modele.elements.*;
import modele.Map;
import util.Vector2f;
import util.Point2d;


@SuppressWarnings("serial")
public class Vue extends VueMap implements KeyListener
{
	
	private int x,y;
	private Point2d window; // position de la fenetre ( Initialement à (0,0) )	
	private int margeX, margeY;
	private boolean altittude,vitesse;
	/**
	 * Constructeur qui permet de créer la vue du jeu (la partie) .
	 *
	 * @param ctrl : le contrôleur de la vue.
	 * @param _x : la position du joueur (abscisses).
	 * @param _y : la position du joueur (ordonnées).
	 *
	 */
	public Vue(ControlerMap ctrl, int _x, int _y) 
	{
		super(ctrl);
		x = _x;
		y = _y;
		window = new Point2d();
		margeX = this.getWidth()/10;
		margeY = this.getHeight()/3;
		this.addKeyListener(this);
		altittude=true;
		vitesse=true;
	}

	/**
	 * Pour bouger l'écran si le joueur se place en bordure.
	 *
	 */
	private void translateWindow()
	{
		margeX = this.getWidth()/10;
		margeY = this.getHeight()/3;

	        // --------------------------
                // Calcul de la position de la fenetre
		// --------------------------
		// --------------------------
                //// Axe des x
                if (getControler().getMap().getPerso().getPosition().getX()+margeX >= (this.getWidth() + window.getX()))
                        window.setX(window.getX() + getControler().getMap().getPerso().getPosition().getX() + margeX - (this.getWidth() + window.getX()));
                else if (getControler().getMap().getPerso().getPosition().getX() <= (window.getX() + margeX) && (window.getX() > 0))
                        window.setX(window.getX() - (margeX - (getControler().getMap().getPerso().getPosition().getX()-window.getX())));
		// --------------------------
		// --------------------------
                //// Axe des y  
                if (getControler().getMap().getPerso().getPosition().getY()-margeY <= (window.getY()))
                        window.setY(window.getY()-(margeY-(getControler().getMap().getPerso().getPosition().getY()-window.getY())));
                else if (getControler().getMap().getPerso().getPosition().getY() >= (window.getY() + (margeY+getHeight()/3)))
                        window.setY(window.getY() + (getControler().getMap().getPerso().getPosition().getY() - (window.getY() + (margeY+getHeight()/3))));
	}

	/**
	 * Dessine l'ensemble des éléments affichés.
	 */
	public void paint(Graphics g)
	{
		// --------------------------
		// Dessin de l'arrière plan
		g.setColor(new Color(20,20,(175+(getControler().getMap().getPerso().getPosition().getY()/100<-175?
					-175:(getControler().getMap().getPerso().getPosition().getY()/100)))));
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
                
		// -------------------------
		// Dessin du sol
		g.setColor(new Color(20,120,10));
		int[] xtab=new int[5],ytab=new int[5];
		// Coordonées des polygones
		for (int i=1;i<getControler().getMap().nbPointSol()-1;i++)
		{
			for (int j=2;j>=0;j--)
			{
				xtab[2-j] = getControler().getMap().getPointSolI(i+1-j).getX()-window.getX();
				ytab[2-j] = getControler().getMap().getPointSolI(i+1-j).getY()-window.getY();
			}
			xtab[3] = getControler().getMap().getPointSolI(i+1).getX()-window.getX();
			xtab[4] = getControler().getMap().getPointSolI(i-1).getX()-window.getX();
			ytab[3] = getHeight();
			ytab[4] = getHeight();
			// Dessin des polygones
			g.fillPolygon(xtab,ytab,5);
		}
		// ---------------------------
		// Barre de progression
		g.setColor (new Color (180,0,0));
		g.fillRect(0,getHeight()-2,(int)((float)getControler().getMap().getPerso().getPosition().getX()/
					   (float)getWidth()*(float)(getControler().getMap().getArrivee())),getHeight());
		g.setColor (new Color (20,0,20));
		g.fillRect((int)((float)getWidth()*((float)getControler().getMap().getPerso().getPosition().getX()/
						(float)getControler().getMap().getArrivee())),getHeight()-2,getWidth(),getHeight());
	        // --------------------------
                // Dessin du perso
		if (getControler().getMap().getPerso().nbImage()>=1)
		{	
			int c = getControler().getMap().getPerso().getCurrentImage();
			g.drawImage(getControler().getMap().getPerso().getImage(c),
					x-15, y-40,30,40,null);
		}
		else
		{
			g.setColor(new Color(240,0,0));
			g.fillRect(x, y-getControler().getMap().getPerso().getSize(),
							getControler().getMap().getPerso().getSize(),
							getControler().getMap().getPerso().getSize());
		}
		// --------------------------
		// Dessin des élements de la map
		Element e;
		int c;
		for (int i=0;i<getControler().getMap().nbElem();i++)
		{
			e = getControler().getMap().getElem(i);
			c = e.getCurrentImage();

			if (e.getEtat() > Element.MORT)
			{
				g.drawImage(e.getImage(c),e.getPosition().getX()-(window.getX()),
						(e.getPosition().getY()-e.getSize()/2)-(window.getY()),e.getSize(),e.getSize(),null);
			}
			else if (e.getEtat() == Element.ATTRAPABLE)
			{
				g.setColor (new Color (200,200,50));
				g.fillOval((e.getPosition().getX())-window.getX(),(e.getPosition().getY()-e.getSize())-window.getY(),
						e.getSize(), e.getSize());
			}
		}
	
		//System.out.print ((int)(255f*(float)(1f/(float)(1f+(float)getControler().getMap().getPerso().getEtat()/10f)))+"\n");
		g.setColor (new Color ((int)Math.abs(255f*(float)(1f/(float)(1f+(float)getControler().getMap().getPerso().getEtat()/40f))),
					(int)Math.abs(255f*((float)getControler().getMap().getPerso().getEtat()/100f)),60));
		g.fillRect (20,28,(int)(100*(float)getControler().getMap().getPerso().getEtat()/(float)Element.PLEINEVIE),5);
		g.setColor (new Color (0,0,0));
		g.fillRect (20+(int)(100*(float)getControler().getMap().getPerso().getEtat()/(float)Element.PLEINEVIE),
				28,100-(int)(100*(float)getControler().getMap().getPerso().getEtat()/(float)Element.PLEINEVIE),5);
		g.setColor (new Color (255,255,255));
		g.drawString(""+getControler().getMap().getPerso().getEtat()+"Pv",140,35);
		if (vitesse){g.drawString("Vitesse "+(int)getControler().getMap().getPerso().getDx().norme()+"km/h",(this.getWidth()/2)-20,35);}
		if (altittude){g.drawString ("Altittude "+((-1)*getControler().getMap().getPerso().getPosition().getY())/10+"m",(this.getWidth()/2)-20,50);}
		g.drawString("ITEM = "+getControler().getMap().getPerso().nbElemAttrap()+" / "+ getControler().getMap().getBut(), getWidth()-100, 35);
	}

	/** redessine tout lors d'un mouvement. */
	public void enMouvement(MouvementEvent event)
	{
		translateWindow();
		if (event != null)
		{
			x = (int) event.getVector().getI()-(window.getX());
			y = (int) event.getVector().getJ()-(window.getY());
		}
		if (getControler().getMap().getPerso().getDx().norme()>400)
		{
			if (getControler().getMap().getPerso().getCurrentImage()<2)
				getControler().getMap().getPerso().setCurrentImage(7);
			else
				getControler().getMap().getPerso().setCurrentImage(6);
		}
		else if (getControler().getMap().getPerso().getCurrentImage()==6)
		{
			getControler().getMap().getPerso().setCurrentImage(0);	
		}
		else if (getControler().getMap().getPerso().getCurrentImage()==7)
		{
			getControler().getMap().getPerso().setCurrentImage(2);
		}
		this.repaint();
	}

	/** Lors d'une pression sur un bouton, permet de contrôler le jeu. */
	public void keyPressed(KeyEvent arg0) 
	{
		if (arg0.getKeyChar() == 'd' || arg0.getKeyChar() == '6' )
		{
			getControler().getMap().getPerso().setCurrentImage 
					((getControler().getMap().getPerso().getCurrentImage()+1)%2);
			getControler().notifierMouvement(new Vector2f(2,0));
		}
		else if (arg0.getKeyChar() == 'q' || arg0.getKeyChar() == '4' )
		{
			getControler().getMap().getPerso().setCurrentImage (3);
			getControler().notifierMouvement(new Vector2f(-2,0));
		}	
		else if (arg0.getKeyChar() == 's' || arg0.getKeyChar() == '5' )
		{
			if (getControler().getMap().getPerso().getCurrentImage()>2 ||
					 getControler().getMap().getPerso().getCurrentImage()==5)
				getControler().getMap().getPerso().setCurrentImage (5);
			else
				getControler().getMap().getPerso().setCurrentImage (4);
			getControler().notifierMouvement(new Vector2f(0,4)); 
		}
		else if (arg0.getKeyChar() == 'z' || arg0.getKeyChar() == '8')
		{
			if (getControler().getMap().getPerso().getDx().getJ()==0)
				getControler().notifierMouvement(new Vector2f(getControler().getMap().getPerso().getDx().getI()/2,15));
		}
		else if (arg0.getKeyCode() == KeyEvent.VK_ESCAPE)
		{
			getControler().getCtrlMenu().changerPanneau(new ChangementMenuEvent(this, 
										ChangementMenuEvent.MENU_PRINCIPAL));
		}
		else if (arg0.getKeyChar() == 'p')
		{
			System.out.print (getControler().isPause()+"\n");
			if (getControler().isPause())
				getControler().suspendre();
			else
				getControler().reprendre();
		}
		else if (arg0.getKeyChar() == 'h')
		{
			altittude = !altittude;
			this.repaint();
		}
		else if (arg0.getKeyChar() == 'v')
		{
			vitesse = !vitesse;
			this.repaint();
		}

	}

	/** Lorsque l'on reste appuyé sur une touche. */
	public void keyReleased(KeyEvent arg0) 
	{
		int current;
		if (getControler().getMap().getPerso().getCurrentImage()==4)
			current = 0;
		else if (getControler().getMap().getPerso().getCurrentImage()==4)
			current = 2;
		else
			current = (getControler().getMap().getPerso().getCurrentImage());
		getControler().getMap().getPerso().setCurrentImage (current);
	}

	public void keyTyped(KeyEvent arg0) 
	{
		
	}

}
