#include <vector>
#include "Solide.h"

using namespace std;

class Solide1D : public Solide
{
private:
	vector<char> element;

	void initialisation();
	void etapeMetropolis();	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.

public:
	Solide1D(unsigned int largeur_var =2, double couplageJ_var =0, double permeabilite_var = 5000.0, double thermostat =0, double champB_var =0)
		:Solide(largeur_var, couplageJ_var, permeabilite_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide1D()	{}

	//Fait évoluer la température du système de tmin à tmax sur plusieurs étapes.
	void evolutionThermique(double tmin, double tmax,unsigned int nbEtapes);

	//Fait évoluer la température du système de tmin à tmax sur plusieurs étapes.
	void evolutionMagnetique(double bmin, double bmax,unsigned int nbEtapes);
};
