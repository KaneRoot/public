import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
/*
	JPanelCompteur est son propre Ecouteur
*/
class JPanelCompteur extends JPanel implements ActionListener
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
		this.add(this.jtfCompteur, BorderLayout.CENTER);

		// son propre écouteur:  actionPerformed(ActionEvent e) dans la classe
		this.jbPlus.addActionListener(this) ;
		this.jbMoins.addActionListener(this) ;
	}
	
	public void actionPerformed(ActionEvent e)
	{
	int entier = Integer.parseInt(this.jtfCompteur.getText()); 
	JButton jb = (JButton)e.getSource();
		
		if( jb == this.jbPlus)
			entier++;
		else
			entier--;
		this.jtfCompteur.setText(""+entier);
	}
}
////////////////////////////////////////////////////////////////////
public class Afficheur3 extends JFrame
{
	JPanelCompteur jpCpt = new JPanelCompteur() ;
	 
	public Afficheur3( String s )
	{
		super(s);
		this.add(jpCpt,BorderLayout.CENTER) ;
	}
	public static void main ( String [] args )// pareil....
	{
	Afficheur3 cpt ;
		cpt = new Afficheur3("Essai 3") ;
		cpt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		cpt.pack() ;
		cpt.setLocation(500,500);
		cpt.setVisible(true) ;		
	}
}