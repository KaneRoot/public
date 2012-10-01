#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>	// Pour générer un nombre aléatoire
#include <cstdlib>	// Pour générer un nombre aléatoire

using namespace std;

void useless() {
	string nom("Bob");
	string& rnom(nom);

	cout << "Hello : " ; 
	cin >> rnom;
	cout << nom << endl << rnom << endl;
	int nbAleatoire(0);
	srand(time(0));
	nbAleatoire = rand() % 5;    
	int* pointeur(0);
	pointeur = new int;

	cout << "Quel est votre age ? ";
	cin >> *pointeur;

	cout << "Vous avez " << *pointeur << " ans." << endl;

	delete pointeur;
	pointeur = 0;
	string const nomFichier("C:/Nanoc/scores.txt");

	ofstream monFlux(nomFichier.c_str()); // c_str récupère l'@ du tableau de char dans l'objet string
}
void moyenne() {
	double moyenne(0);
	vector<double> notes; //Un vecteur vide

	notes.push_back(12);
	notes.push_back(14.5);
	notes.push_back(15);

	for(int i(0); i<notes.size(); ++i)
		moyenne += notes[i];

	moyenne /= notes.size();

	cout << "Votre moyenne est : " << moyenne << endl;
}
void test_ref_objet(string &s) {
	cout << s << endl;
}
void test_strings() {
	string prenom("Albert"); 
	string nom("Einstein");
	string total;

	total += prenom;
	total += " ";
	total += nom;

	cout << "Vous vous appelez " << total << "." << endl; 
	test_ref_objet(total);
}
int main() {
	//useless();
	// il faut toujours faire cin.ignore() après la ligne "cin >> a"
	//moyenne();
	// Personnage::Personnage(string nomArme, int degatsArme) : m_vie(100), m_mana(100), m_nomArme(nomArme), m_degatsArme(degatsArme) { }
	// Personnage::~Personnage() { }
	test_strings();
	return 0;
}
