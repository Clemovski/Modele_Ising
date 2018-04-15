#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Imprimante
{
private:
	static Imprimante* pInstance;
    unsigned int compteurWeiss;
	string nomFichierMesures;
	fstream fichierMesures;
	string nomFichierWeiss;
	fstream fichierWeiss;

public:
	static Imprimante* instance()
	{
		if (pInstance == 0)	pInstance = new Imprimante();

		return pInstance;
	}

	Imprimante();
	~Imprimante();

	//Change le fichier de mesures et ferme le précédent.
	void setFichierMesures(string nouveauFichier);

    //Saute deux lignes dans le fichier Weiss pour indiquer un nouveau bloc de données.
    void nextFichierWeiss();

	//Lit dans un fichier les paramètres qui devront être utilisés pour le programme.
	map<string, double> lire(string nomFichierLecture);

	//Ecrit dans un fichier les valeurs passée en argument.
	void ecrireMesures(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi);

    //Ecrit les positions des spins up.
    void ecrirePosition(unsigned int x, unsigned int y, unsigned int z);
    void ecrirePosition(unsigned int x, unsigned int y);
    void ecrirePosition(unsigned int x);

	//Ecrit dans la console
	void console(string message)	{ cout << message << endl; }
	//Affiche le chargement
	void chargement(int pourcent);
};
