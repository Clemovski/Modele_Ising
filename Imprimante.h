#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Imprimante
{
private:
	static Imprimante* pInstance;
	string nomfichierEcriture;
	fstream fichierEcriture;

public:
	static Imprimante* instance()
	{
		if (pInstance == 0)	pInstance = new Imprimante();

		return pInstance;
	}

	Imprimante();
	~Imprimante();

	//Lit dans un fichier les paramètres qui devront être utilisés pour le programme.
	void lire(string nomFichierLecture);

	//Ecrit dans un fichier les valeurs passée en argument.
	void ecrire(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi);

	//Ecrit dans la console
	void console(string message)	{ cout << message << endl; }
	//Affiche le chargement
	void chargement(int pourcent);
};
