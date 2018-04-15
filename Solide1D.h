#ifndef _SOLIDE1D
#define _SOLIDE1D
#include <vector>
#include "Solide.h"

using namespace std;

class Solide1D : public Solide
{
private:
	vector<char> element;

	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.
	void etapeMetropolis();
	//Initialise le solide
	void initialisation();
    //Ecrit dans un fichier les positions des spins Up.
    virtual void ecrirePositionsSpins();
    

public:
	Solide1D(unsigned int largeur_var =2, double couplageJ_var =0, double thermostat =0, double champB_var =0) : Solide(largeur_var, couplageJ_var, thermostat, champB_var)
		{ initialisation(); }
	~Solide1D()	{}
};

#endif
