package modele;

/** Import des différentes librairie **/
import java.util.ArrayList;
import javax.swing.event.EventListenerList;
/** Import des différents packetage **/
import modele.listener.MouvementListener;
import util.Point2d;
import modele.elements.*;


/**
 * Carte du jeu.
 *
 * Contient les éléments affichés, ainsi que le personnage.
 */

public class Map
{
	private ArrayList<Point2d> sol_;
	private ArrayList<Element> elem_;

	private float masse;   	/* Pour le calcul du mouvement */
	private int w_,h_; 	/* w_ indique la largeur et h_ indique la hauteur */
	private int arrivee; 	/* Coordonné X de l'arrivée */
	private int but;	/* Nombre d'item a récupéré */
	private E_perso perso_;
	private EventListenerList ecouteurs_;
	private String nom = null;

	/**
	 * Ce constructeur va servir pour faire une copie de la carte courante.
	 *
	 */
	public Map(int w, int h, float masse, E_perso e, ArrayList<Point2d> sol, ArrayList<Element> elements, String nom, EventListenerList ecouteurs, int but)
	{
		setW(w);
		setH(h);
		setPerso(e);
		setNom(nom);
		setSol(sol);
		setEcouteurs(ecouteurs);
		setMasse(masse);
		setBut(but);
	}
	
	public Map (int w,int h, E_perso e)
	{
		elem_ = new ArrayList<Element>(1);
		sol_ = new ArrayList<Point2d>(2);
		setW(w);
		setH(h);
		setPerso(e);
		ecouteurs_ = new EventListenerList();
		setMasse(100);
		setBut(0);
	}

	/**
	 * Constructeur vide.
	 */
	public Map()
	{
		this(0,0,null);
	}
	
	/** Défini tous les points du sol en une fois. */
	public void setSol(ArrayList<Point2d> sol) { this.sol_ = sol; }

	/** Défini tous les écouteurs de la carte en une fois. */
	public void setEcouteurs(EventListenerList ecouteurs) { this.ecouteurs_ = ecouteurs; }

	/** Défini l'arrivée. */
	public void setArrivee(int a) { this.arrivee = a; }

	/** Défini le nom de la carte. */
	public void setNom(String lenom) { this.nom = lenom; }

	/** Renvoie le nom de la carte. */
	public String getNom() { return this.nom; }

	/** Renvoie la coordonnée X de l'arrivée en fin de partie. */
	public int getArrivee() { return this.arrivee; }

	/** 
	 * Ajout d'un écouteur du mouvement. 
	 * 
	 * @param ml : va écouter le mouvement.
	 *
	 */
	public void ajouterEcouteurMouvement (MouvementListener ml)
	{
		ecouteurs_.add(MouvementListener.class, ml);
	}
	
	public void enleverEcouteurMouvement (MouvementListener ml)
	{
		ecouteurs_.remove(MouvementListener.class, ml);
	}

	/** 
	 * Ajout d'un élément. 
	 * 
	 * @param e : l'élément à ajouter. 
	 * 
	 */
	public void addElem(Element e) 
	{ 
		if (e.getClass().getName()==E_item.class.getName())
		{
			but++;
		}
		elem_.add(e); 
	}

	/** Renvoie le nombre d'éléments de la carte. */
	public int nbElem()	{ return elem_.size(); }

	/** Renvoie le énième élément de la carte. */
	public Element getElem(int i) { return elem_.get(i); }

	/** 
	 * Ajoute un point du sol.
	 * 
	 * @param sol : les coordonnées d'un point à relier aux autres pour former le sol.
	 *
	 */
	public void addPoint(Point2d sol) { sol_.add(sol); }
	
	/** Renvoie le nombre de points formant le sol. */
	public int nbPointSol() { return sol_.size(); }
	
	/** 
	 * Renvoie le énième point du sol. 
	 * 
	 * @param i : le énième point qui forme le sol.
	 *
	 * */
	public Point2d getPointSolI(int i) { return sol_.get(i); }
	
	/** 
	 * Renvoie la hauteur du sol à une coordonnée X passée en paramètre. 
	 * @param x : la coordonnée des abscisses.
	 * */
	public int getYSol(int x) 
	{
		int i;
		for (i=0;! (sol_.get(i).getX() < x && sol_.get(i+1).getX() >= x) && 
				i < sol_.size()-2 ; i++);
		float r = (float)(sol_.get(i+1).getY()-sol_.get(i).getY())
			/ (float)(sol_.get(i+1).getX()-sol_.get(i).getX());

		return (int)(r*(x-sol_.get(i).getX()) + sol_.get(i).getY());
	}

	/** Défini la largeur de la carte. */
	public void setW(int w) { this.w_ = w; }

	/** Renvoie la largeur de la carte. */
	public int getW() { return w_; }

	/** Renvoie le nombre d'item à récupérer */
	public int getBut () { return but; }
	
	/* Définie le nombre d'objet à récupérer */
	public void setBut (int b) { but = b; }

	/** Définie la hauteur de la carte. */
	public void setH(int h) { this.h_ = h; }

	/** Renvoie la hauteur de la carte. */
	public int getH() { return h_; }

	/** Définie le personnage de la carte. */
	public void setPerso(E_perso stick) { this.perso_ = stick; }

	/** Renvoie le personnage de la carte. */
	public E_perso getPerso() { return perso_; }

	/** Modifie la masse de la carte. */
	public void setMasse(float masse) { this.masse = masse; }

	/** Renvoie la masse de la carte. */
	public float getMasse() { return masse; }

	/**
	 * Proposera à terme de renvoyer une copie de la carte.
	 *
	 */
	public Map copie()
	{
		ArrayList<Element> nouveaux_elements = new ArrayList<Element>(10);
		ArrayList<Point2d> nouveau_sol = new ArrayList<Point2d>(10);

		// Faire une copie du perso
		E_perso nouveau_perso = getPerso();

		// quand on saura faire : ajouter une copie des éléments
		for(Element e : this.elem_)
			nouveaux_elements.add(e);

		for(Point2d p : this.sol_)
			nouveau_sol.add(p);

		return new Map(getW(), getH(), getMasse(), 
				nouveau_perso, nouveau_sol, nouveaux_elements, 
				getNom(), this.ecouteurs_,this.getBut());
	}
}
