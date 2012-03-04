import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
/*
	une classe Ecouteur  par bouton avec JPanelCompteur en attribut
	appel de procédures plus/moins de la classe JPanelCompteur

*/
class JPanelCompteur extends JPanel
{
	private JButton jbPlus = new  JButton ("+");
	private JButton jbMoins= new  JButton ("-") ;
	private JTextField jtfCompteur =  new  JTextField("0");

	public JPanelCompteur()
	{
		Font f = new Font("Serif", Font.PLAIN, 36); // par exemple
		BorderLayout bl = new BorderLayout() ;
		this.setLayout(bl) ;
		this.jbPlus.setFont(f); 
		this.jbMoins.setFont(f); 
		this.jtfCompteur.setFont(f); 
		
		this.add(jbPlus, BorderLayout.EAST) ;
		this.add(jbMoins, BorderLayout.WEST) ;
		
		this.jtfCompteur.setHorizontalAlignment(JTextField.RIGHT);
		this.jtfCompteur.setEnabled(false);
		
		this.add(jtfCompteur, BorderLayout.CENTER);
		
		ActionListener alplus = new EcouteurPlus(this);
		this.jbPlus.addActionListener(alplus) ;
		ActionListener almoins = new EcouteurMoins(this);
		this.jbMoins.addActionListener(almoins) ;
	}
	
	public void plus()
	{
	int entier = Integer.parseInt(this.jtfCompteur.getText()); 
		entier++;
		this.jtfCompteur.setText(""+entier);
	
	}
	public void moins()
	{
	int entier = Integer.parseInt(this.jtfCompteur.getText()); 
		entier--;
		this.jtfCompteur.setText(""+entier);
	}
}
////////////////////////////////////////////////////////////////////


class EcouteurPlus implements ActionListener
{
	private JPanelCompteur jpcpt ;

	public EcouteurPlus( JPanelCompteur jp)
	{
		jpcpt = jp ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		jpcpt.plus();
	}
}
class EcouteurMoins implements ActionListener
{
	private JPanelCompteur jpcpt ;

	public EcouteurMoins( JPanelCompteur jp)
	{
		jpcpt = jp ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		jpcpt.moins();
	}
}
////////////////////////////////////////////////////////////////////////////
public class Afficheur1 extends JFrame
{
	JPanelCompteur jpCpt = new JPanelCompteur() ;
	 
	public Afficheur1( String s )
	{
	super(s);
	this.add(jpCpt,BorderLayout.CENTER) ;
	}
	
	public static void main ( String [] args )
	{
	Afficheur1 cpt ;
		cpt = new Afficheur1("Essai compteur") ;
		cpt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		cpt.pack() ;
		cpt.setLocation(100,100);
		cpt.setVisible(true) ;		
	}
}
