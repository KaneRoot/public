import org.omg.CORBA.* ;
import java.awt.* ; 
import java.applet.Applet ;
import java.awt.event.* ;
import java.io.* ;

public class Client 
	extends Applet
	implements ActionListener
{
  TextField texte = new TextField("",10) ;
  Label intitule = new Label("Nom a rechercher : ") ;
  Button bouton = new Button("Envoie") ;
  Annuaire annuaire ;

  public void init()
	{
		String ior ;

		add(intitule) ;
		add(texte) ;
		add(bouton) ;
		bouton.addActionListener(this) ;

		try
		{
	    ORB orb = ORB.init(new String[0], null ) ;
	    System.out.println( "0) ORB initialise'") ;

	    FileReader file = new FileReader(iorfile.value) ;
	    BufferedReader in = new BufferedReader(file) ;
	    ior = in.readLine() ;
	    file.close() ;

//	    ior = getParameter("adresse") ;
	    System.out.println( "1) IOR lue : " + ior ) ;

	    org.omg.CORBA.Object obj = orb.string_to_object(ior) ;
	    annuaire = AnnuaireHelper.narrow(obj) ;
		}
		catch( Exception ex )
		{
			System.err.println( "Erreur !!" ) ;
	    ex.printStackTrace() ;
		}
  }

  public void actionPerformed(ActionEvent ae)
	{
		try
		{
	    String texte1= texte.getText() ;
	    StringHolder message = new StringHolder() ;

	    annuaire.chercheNom(texte1, message) ;
	    intitule.setText(message.value) ;
		}
		catch (Exception e)
		{
	    System.out.println(e.getMessage()) ;
	    e.printStackTrace() ;
		}
  }

}

