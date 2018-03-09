#include <vector>
#include <string>

using namespace std;

class Imprimante
{
private:
	static Imprimante* instance;
	string nomFichier;

public:
	static Imprimante* Imprimante::Instance()
	{
		if (instance == 0)
		{
			instance = new Imprimante();
		}

		return instance;
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
