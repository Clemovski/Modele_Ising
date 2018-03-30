#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Imprimante
{
private:
	static Imprimante* pInstance;
	string nomFichier;
	fstream fichier;

public:
	static Imprimante* instance()
	{
		if (pInstance == 0)	pInstance = new Imprimante();

		return pInstance;
	}

	Imprimante();
	~Imprimante();

	//Ecrit dans un fichier les valeurs passée en argument.
	void ecrire(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi);

	//Ecrit dans la console
	void console(string message)	{ cout << message << endl; }
	//Affiche le chargement
	void chargement(int pourcent);
};
