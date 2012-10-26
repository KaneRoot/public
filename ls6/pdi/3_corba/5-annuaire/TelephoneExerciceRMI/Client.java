import java.awt.*; 
import java.rmi.*; 
import java.applet.Applet;
import java.awt.event.*;
import java.net.InetAddress.* ;
import java.net.* ;

public class Client 
    extends Applet
    implements ActionListener {

    TextField texte = new TextField("",10);
    Label intitule = new Label("Nom a rechercher : ");
    Button bouton = new Button("Envoie");
    Annuaire annuaire;

    public void init() {
	add(intitule);
	add(texte);
	add(bouton);
	bouton.addActionListener(this);

	try {
	    String hostname = super.getParameter("serveur");
	    annuaire = (Annuaire)
		Naming.lookup("rmi://"+hostname+"/LAnnuaire");
	} catch (Exception e) {
	    System.err.println(e);
	    e.printStackTrace();
	}
    }

    public void actionPerformed(ActionEvent ae) {
	try {
	    String message = annuaire.chercheNom(texte.getText());
	    intitule.setText(message);
	} catch (Exception e) {
	    System.out.println(e.getMessage());
	    e.printStackTrace();
	}
    }
}
