#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Imprimante
{
private:
	static Imprimante* pInstance;
	string nomFichier;

public:
	static Imprimante* instance()
	{
		if (pInstance == 0)
		{
			pInstance = new Imprimante();
		}

		return pInstance;
	}

	Imprimante() { nomFichier = "truc.txt"; };
	~Imprimante() {};

	//Ecrit dans un fichier.
	void ecrire();
	//Lit le contenu d'un fichier
	void lire();
	//Ecrit dans la console
	void console(string message)	{ cout << message << endl; }
};
