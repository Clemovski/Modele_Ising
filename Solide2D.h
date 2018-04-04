#include <vector>
#include "Solide.h"

using namespace std;

class Solide2D : public Solide
{
private:
	vector<vector<char>> element;

	void initialisation();
	void etapeMetropolis();	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.

public:
	Solide2D(unsigned int largeur_var =2, double couplageJ_var =0, double thermostat =0, double champB_var =0)
		:Solide(largeur_var, couplageJ_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide2D()	{}

	//Fait évoluer la température du système de tmin à tmax sur plusieurs étapes.
	void evolutionThermique(double tmin, double tmax,unsigned int etapes);
};
