#include "Solide.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include "Solide3D.h"

class SolideFactory {
private :
	static SolideFactory* pInstance;

public :
	static SolideFactory* instance()
	{
		if (pInstance == 0)	pInstance = new SolideFactory();

		return pInstance;
	}

	SolideFactory() {}
	~SolideFactory() {}

	Solide* create(unsigned int dimension, unsigned int largeur, double couplageJ, double thermostat, double champB)
	{
		if(dimension == 1)
		{
			return new Solide1D(largeur, couplageJ, thermostat, champB);
		}
		else if(dimension == 2)
		{
			return new Solide2D(largeur, couplageJ, thermostat, champB);
		}
		else if(dimension == 3)
		{
			return new Solide3D(largeur, couplageJ, thermostat, champB);
		}
		else return NULL;
	}
};

//Définition de l'instance
SolideFactory* SolideFactory::pInstance;
