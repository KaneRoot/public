import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
/*
	une classe Ecouteur  par bouton avec JTextField en attribut

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
		
		ActionListener alplus = new EcouteurPlus(this.jtfCompteur);
		this.jbPlus.addActionListener(alplus) ;
		ActionListener almoins = new EcouteurMoins(this.jtfCompteur);
		this.jbMoins.addActionListener(almoins) ;
	}
}
class EcouteurPlus implements ActionListener
{
	private JTextField jtfcpt ;

	public EcouteurPlus( JTextField jtf)
	{
		jtfcpt = jtf ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		int entier = Integer.parseInt(this.jtfcpt.getText()); 
		entier++;
		this.jtfcpt.setText(""+entier);
	}
}

class EcouteurMoins implements ActionListener
{
	private JTextField jtfcpt ;

	public EcouteurMoins( JTextField jtf)
	{
		jtfcpt = jtf ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		int entier = Integer.parseInt(this.jtfcpt.getText()); 
		entier--;
		this.jtfcpt.setText("" + entier);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
public class Afficheur extends JFrame
{
	JPanelCompteur jpCpt = new JPanelCompteur() ;
	 
	public Afficheur( String s )
	{
		super(s);
	
		this.add(jpCpt,BorderLayout.CENTER) ;
		
	}
	
	public static void main ( String [] args )
	{
		Afficheur cpt ;
		cpt = new Afficheur("Essai compteur") ;
		cpt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		cpt.pack() ;
		cpt.setLocation(100,100);
		cpt.setVisible(true) ;		
	}
}
