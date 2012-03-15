/**
 * Définition de la classe Test
 */

package test;

/**
 *
 */
public class Test
{

    public static void main(String[] args)
    {
        modèle.PointModèle modèle = new modèle.PointModèle(0, 0);
        contrôleur.PointContrôleur contrôleur = new contrôleur.PointContrôleur(modèle);
        contrôleur.AfficherVues();
    }

}
