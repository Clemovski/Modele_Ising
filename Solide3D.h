#ifndef _SOLIDE3D
#define _SOLIDE3D
#include <vector>
#include "Solide.h"

using namespace std;

class Solide3D : public Solide
{
private:
	vector< vector <vector<char> > > element;

	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.
	void etapeMetropolis();
	//Initialise le solide
	void initialisation();
    //Ecrit dans un fichier les positions des spins Up.
    virtual void ecrirePositionsSpins();

public:
	Solide3D(unsigned int largeur_var =2, double couplageJ_var =0, double thermostat =0, double champB_var =0) : Solide(largeur_var, couplageJ_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide3D()	{}
};

#endif
