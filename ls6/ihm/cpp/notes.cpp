// Constructeur de copie
Personnage::Personnage(Personnage const& personnageACopier) : m_vie(personnageACopier.m_vie), m_mana(personnageACopier.m_mana), m_arme(0)
{
	m_arme = new Arme(*(personnageACopier.m_arme));
}

Guerrier::Guerrier() : Personnage(), m_vie(1000) 
{
}
/*
	Méthodes virtual : 
		à déclarer dans le .h pas dans le .cpp
*/
class Vehicule
{
	public:
	virtual void affiche() const;
};

class Voiture: public Vehicule
{
	public:
	virtual void affiche() const; // pas obligatoire de mettre virtual dans la classe fille
};

void presenter(Vehicule const& v)
{	// fonction de la classe Vehicule ou ses filles
	// C'est de la résolution dynamique des liens
	v.affiche();
}
/*
	Pas d'appel de méthodes virtuelles dans les constructeurs
	Un destructeur doit toujours être virtual


	Méthode virtuelle pure :
		virtual int nbrRoues() const = 0; 
	On n'a pas à implémenter la fonction dans la classe, on le fera dans une classe fille

			
	Une méthode virtuelle peut être redéfinie dans une classe fille.
	Une méthode virtuelle pure doit être redéfinie dans une classe fille.
	Si un classe a une méthode virtuelle pure, elle est abstraite.

	On peut déclarer un attribut statique et privé, mais il faut l'initialisé en dehors de la classe et d'une fonction (main y compris).
	On le fait généralement dans le .cpp de la classe. Exemple :
	int Maclasse::Monattribut = 0;
*/

