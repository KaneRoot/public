import javax.swing.*;
import java.awt.*;

public class LanceurApplication
{
	public static void main(String[] args)
	{
		JTPersonne personne = new JTPersonne("Bla");
		personne.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		personne.pack();
		personne.setVisible(true);
	}
}
