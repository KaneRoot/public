import javax.swing.*;
import java.awt.*;
import java.util.Vector;
import javax.swing.table.*;
import java.util.ArrayList;
import javax.swing.text.*;
import javax.swing.event.*;

public class JTPersonne extends JFrame
{
	JLabel label = new JLabel("Nom : ");
	JTextField jtf_nom = new JTextField("",20);
	JPanel jp_haut = new JPanel();
	JPanel jp_bas = new JPanel();
	Vector<String> idColonnes;
	Vector<Vector<String>> data = new Vector<Vector<String>>();
	DefaultTableModel dtm;
	JTable jt_personne;
	ArrayList<Personne> array_personne;
	Document doc = new NumericDocument();
	
	public JTPersonne(String s)
	{
		super(s);
		this.add(jp_haut,BorderLayout.NORTH);
		this.jp_haut.add(label);
		this.jp_haut.add(jtf_nom);
		array_personne = EssaisPersonnes.lirePersonne("fichierPersonne.txt");
		jtf_nom.setDocument(doc);
		doc.addDocumentListener(new JTPEcouteur(this));
		
		idColonnes = new Vector<String>();
		idColonnes.add("Nom");
		idColonnes.add("Prénom");
		idColonnes.add("Date de Naissance");
		
		this.data = toDataVector(array_personne);
		
		dtm = new DefaultTableModel();
		dtm.setDataVector(data,idColonnes);
		jt_personne = new JTable(dtm);
		JScrollPane jsp = new JScrollPane(jt_personne);
		this.add(jp_bas,BorderLayout.SOUTH);
		this.jp_bas.add(jsp);
		
	}
	public static Vector<String> toLigne(Personne p) 
	{
		Vector<String> maligne;
		maligne = new Vector<String>();
		maligne.add(p.getNom());
		maligne.add(p.getPrenom());
		maligne.add(p.getDateNaissance().toString());
		
		return maligne;
	}
	public static Vector<Vector<String>> toDataVector(ArrayList<Personne> personnes) 
	{
		Vector<Vector<String>> monDataVecteur = new Vector<Vector<String>>();
		Vector<String> ligne;
		for(Personne bla : personnes)
		{
			ligne = new Vector<String>();
			ligne = JTPersonne.toLigne(bla);
			monDataVecteur.add(ligne);
		}
		return monDataVecteur;
	}
	public void miseAJour()
	{
		ArrayList<Personne> tmp = EssaisPersonnes.extraire(this.array_personne,this.jtf_nom.getText());
		this.data = JTPersonne.toDataVector(tmp);
		this.dtm.setDataVector(this.data, idColonnes);
	}
}
