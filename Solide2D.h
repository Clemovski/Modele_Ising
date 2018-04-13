#ifndef _SOLIDE2D
#define _SOLIDE2D
#include <vector>
#include "Solide.h"

using namespace std;

class Solide2D : public Solide
{
private:
	vector<vector<char>> element;

	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.
	void etapeMetropolis();
	//Initialise le solide
	void initialisation();

public:
	Solide2D(unsigned int largeur_var =2, double couplageJ_var =0, double thermostat =0, double 			champB_var =0) : Solide(largeur_var, couplageJ_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide2D()	{}
};

#endif
