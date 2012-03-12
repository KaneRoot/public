import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
/*
	une  seule classe Ecouteur  pour les deux boutons avec JTextField en attribut
	utilisation du getText() pour reconnaitre les boutons
*/
class JPanelCompteur extends JPanel
{
	private JButton jbPlus = new  JButton ("+");
	private JButton jbMoins= new  JButton ("-") ;
	private JTextField jtfCompteur =  new  JTextField("0000000");

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
		
		ActionListener alplusmoins = new EcouteurPlusMoins(this.jtfCompteur);
		this.jbPlus.addActionListener(alplusmoins) ;
		this.jbMoins.addActionListener(alplusmoins) ;
	}
}
class EcouteurPlusMoins implements ActionListener
{
	private JTextField jtfcpt ;

	public EcouteurPlusMoins( JTextField jtf)
	{
		jtfcpt = jtf ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
	int entier = Integer.parseInt(this.jtfcpt.getText()); 
	JButton jb = (JButton)e.getSource();
		
		if(jb.getText().equals("+"))
			entier++;
		else
			entier--;
		this.jtfcpt.setText(""+entier);
	}
}

public class Afficheur2 extends JFrame
{
	JPanelCompteur jpCpt = new JPanelCompteur() ;
	 
	public Afficheur2( String s )
	{
		super(s);
	
		this.add(jpCpt,BorderLayout.CENTER) ;
		
	}
	
	public static void main ( String [] args )
	{
		Afficheur2 cpt ;

		cpt = new Afficheur2("Essai compteur") ;
		cpt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		cpt.pack() ;
		cpt.setLocation(500,500);
		cpt.setVisible(true) ;		
	}
}
