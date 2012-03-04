// IHM de loto
// avec modifications
//et extensions

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.text.*;

class Loto1 extends JFrame
{
   private JLabel jl_coches = new JLabel("Numeros coches");
   private JTextField jtf_coches = new JTextField("0", 3);
   private JCheckBox[] jcb_numeros = new JCheckBox[49];
   private JButton jb_valider = new JButton("Valider");
   //nb de cases cochees
   private int nb_coche=0;

   //Améliorations:
   private JTextField jtf_nom=new JTextField(20); //nom du joueur
   private JLabel jl_nom = new JLabel("Nom :");
   private JButton jb_effacer=new JButton("Effacer");   
   private JTextField jtf_nbchiffre=new JTextField(5);  //Total de nombres a cocher
   private JLabel jl_nbchiffre = new JLabel("Total de nombres à cocher :");
   private int nbC=0;	// doit correspondre au contenu de jtf_nbchiffre.
	
   public Loto1(String titre)
   {
   	super(titre);
	
	GridLayout gl_numeros=new GridLayout(7,7);
	JPanel jp_num=new JPanel(gl_numeros);
	JPanel jp_coches=new JPanel();
	JPanel jp_nom=new JPanel();
    JPanel jp_buttons=new JPanel();
	JPanel jp_cochbtn=new JPanel();
	JPanel jp_chiffre=new JPanel();
	JPanel jp_nomchiffre=new JPanel(new BorderLayout());
   
	ItemListener itemEcouteur=new IL_Cocher(this);
	
	//initialisation des 49 coches
	for(int i=0;i<jcb_numeros.length;i++)
	{
	   jcb_numeros[i]=new JCheckBox(""+(i+1));
	   jp_num.add(jcb_numeros[i]);
	   jcb_numeros[i].addItemListener(itemEcouteur);
	}
	//nb de cases cochees (ajout dans le pannel jp_coches)
	jtf_coches.setEditable(false);
	jp_coches.add(jl_coches,BorderLayout.WEST);
	jp_coches.add(jtf_coches,BorderLayout.EAST);
	
	//bouton valider:
	jb_valider.setEnabled(false);
	ActionListener al_valider=new AL_Btn(this);
	jb_valider.addActionListener(al_valider);
	
	//bouton effacer:
	jb_effacer.setEnabled(false);
	ActionListener al_effacer=new AL_Btn(this);
	jb_effacer.addActionListener(al_effacer);
	
	//ajout du controle de saisie pour le total de cases cochees:
	Document doc=new NumericDocument();
	jtf_nbchiffre.setDocument(doc);
	ActionListener majNbC = new AL_jtf(this);
	jtf_nbchiffre.addActionListener(majNbC);
	
	//ajout des objets du nom et du total de chiffre dans un pannel special jp_nom
	jp_nom.add(jl_nom);
	jp_nom.add(jtf_nom);
	jp_chiffre.add(jl_nbchiffre);
	jp_chiffre.add(jtf_nbchiffre);
	jp_nomchiffre.add(jp_nom,BorderLayout.NORTH);
	jp_nomchiffre.add(jp_chiffre,BorderLayout.SOUTH);
	
	//ajout des boutons dans un pannel special jp_buttons
	jp_buttons.add(jb_effacer);
	jp_buttons.add(jb_valider);
	
	jp_cochbtn.add(jp_coches, BorderLayout.WEST);
	jp_cochbtn.add(jp_buttons,BorderLayout.EAST);
	//positionnement des objets dans la JFrame
	this.add(jp_nomchiffre,BorderLayout.NORTH);
	this.add(jp_num,BorderLayout.CENTER);  //tableau de coches au nord de la JFrame
	this.add(jp_cochbtn, BorderLayout.SOUTH);
   }// fin constructeur

   public void majNbC()
   {	
   //nb de case a cocher
	this.nbC=Integer.parseInt(jtf_nbchiffre.getText());
  	if(this.nbC >= jcb_numeros.length)
	   		this.nbC=jcb_numeros.length-1;
	if(this.nbC <= 0)	this.nbC = 1;	
	this.jtf_nbchiffre.setText(""+ this.nbC);
	this.jb_valider.setEnabled(nb_coche==nbC && nbC!=0.);
	}
	
   public void cocher( boolean selected)
   {
	    if(selected)
			this.nb_coche++;
		else
			this.nb_coche--;
  	 //on met a jour le nb de case cochees 
	 jtf_coches.setText(""+nb_coche);
	 //  on ne peut effacer que lorsqu'on a une case cochee
	 jb_effacer.setEnabled(nb_coche!=0);
	//  on ne peut valider que lorsqu'on a atteint le bon nombre
	 jb_valider.setEnabled(nb_coche==nbC && nbC!=0.);
	 
    }
   
   public void valider()
   {
   	 Vector<Integer> vect=new Vector<Integer>();
   	 //ajout des num de cases cochees dans le vecteur
   	  if(!jtf_nom.getText().isEmpty())
   	  {
   	    for(int i=0;i<jcb_numeros.length;i++)
	    {
	      if(jcb_numeros[i].isSelected())
	      {
	        vect.add(i+1);
	      }
	    }
	    //affichage avec bip
	 	//Toolkit.getDefaultToolkit().beep();
	    System.out.println("Grille choisie pour "+jtf_nom.getText()+" : "+vect);
	  }
   }
   
   public void effacer()
   {
   	  for(int i=0;i<jcb_numeros.length;i++)
	  {
	    if(jcb_numeros[i].isSelected())
	    {
	      jcb_numeros[i].setSelected(false);
	    }
  	  }
	  this.nb_coche = 0;
  	  //Toolkit.getDefaultToolkit().beep();
  	  //on met a jour le nb de case cochees 
	 jtf_coches.setText("0");
	 //  on ne peut effacer que lorsqu'on a une case cochee
	 jb_effacer.setEnabled(false);
	 jb_valider.setEnabled(false);
   }
	
//--------------- main: -------------------------
   public static void main(String[] args)
   {
	JFrame jf;
	
	jf=new Loto1("Loto");
	jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	jf.pack(); //calcul la taille optimale de la fenetre;
	jf.setVisible(true);
   }//fin main
}//fin class
