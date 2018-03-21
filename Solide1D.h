#include <vector>
#include "Solide.h"

using namespace std;

class Solide1D : public Solide
{
private:
	vector<char> element;

	void initialisation();
	void etapeMetropolis();	//Fait changer de sens certains spins du système selon la méthode métropolis. Une seule itération.

public:
	Solide1D(int largeur_var =2, double couplageJ_var =0, double magneton_var =0, double thermostat =0, double champB_var =0)
		:Solide(largeur_var, couplageJ_var, magneton_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide1D()	{}
};
