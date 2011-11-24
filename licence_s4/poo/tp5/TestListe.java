public class TestListe
{
	public static void main(String[] argv)
	{
		Liste l = new Liste();
		l.insererDebut("Coucou");
		l.insererDebut("C'est");
		l.insererDebut("Moaaaaa !");
		l.insererFin("FINNNNNNN");
		l.insererPositionDonnee("Truc", 0);
		l.insererPositionDonnee("Truc", 2);
		l.insererPositionDonnee("Truc", 4);
		l.insererFin("FINNNNNNN");
		l.insererFin("FINNNNNNN");
		System.out.println("Test : " + l);
	}
}
