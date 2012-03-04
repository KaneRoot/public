import java.lang.String;
import java.util.Date;
import java.text.DateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.util.Locale;
import java.text.Collator;

public class Personne
{
	private String nom,prenom;
	private Date dateNaissance;
	
	public Personne(String n, String p, Date d)
	{
		this.nom = n;
		this.prenom = p;
		this.dateNaissance = (Date)d.clone();
	}
	public String getNom()
	{
		return this.nom;
	}
	public String getPrenom()
	{
		return this.prenom;
	}
	public Date getDateNaissance()
	{
		return this.dateNaissance;
	}
	public int getJourNaissance()
	{
		Calendar cl = Calendar.getInstance();
		cl.setTime(this.dateNaissance);
		return cl.get(Calendar.DAY_OF_MONTH);
	}
	public int getMoisNaissance()
	{
		Calendar cl = Calendar.getInstance();
		cl.setTime(this.dateNaissance);
		return cl.get(Calendar.MONTH);
	}
	public int getAnneeNaissance()
	{
		Calendar cl = Calendar.getInstance();
		cl.setTime(this.dateNaissance);
		return cl.get(Calendar.YEAR);
	}

	public String toString()
	{
		DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT,Locale.FRANCE);
		return ""+this.nom +" "+this.prenom + " " + df.format(this.dateNaissance);
	}
	public static Date toDate(String d) // d = date en chaîne de caractères
	{
		String[] date = d.split("/");
		Calendar cal = Calendar.getInstance();
		int jour = Integer.parseInt(date[0]);
		int mois = Integer.parseInt(date[1]);
		int annee = Integer.parseInt(date[2]);		
		cal.set(annee,mois,jour);
		return cal.getTime();
	}
	public int compareTo(Personne p) // si on utilise Comparable<Personne>
	{
		Collator frCol= Collator.getInstance(Locale.FRENCH);
		int res = frCol.compare(this.nom,p.nom);
		if ( res == 0)
			res = frCol.compare(this.prenom,p.prenom);
		if ( res == 0)
			res = this.dateNaissance.compareTo(p.dateNaissance);	
		return res;
	}
}
