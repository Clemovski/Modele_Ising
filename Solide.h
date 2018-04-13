#ifndef _SOLIDE
#define _SOLIDE
#include <time.h>	//time(NULL) pour initialisation des variables aléatoires

class Solide
{
protected:
	unsigned int largeur;	//N = Nombre d'élément par côté du solide
	unsigned int limite;	//largeur-1. Redondant mais sert à accélérer le calcul.
	double couplageJ;	//J
	double champB;		//B
	double temperature;	//T = thermostat puisque le système est à l'équilibre. (ensemble canonique)
	double kbT;		//kbT = Boltzmann*Temperature en eV. Redondant mais sert à accélérer le calcul.
	double champBmuB;	//Magneton de Bohr * champB. Redondant mais sert à accélérer le calcul.

	double energie;		//E Energie instantannée du solide
	double energieMoy;	//Energie moyenne calculée
	double sigmaEnergie;	//Ecart type de l'énergie calculé

	double momentMag;	//M Moment magnétique instantannée
	double momentMagMoy;	//Moment magnétique moyen calculé
	double sigmaMomentMag;	//Ecart type du moment magnétique calculé

	int etapes;		//Nombre d'étapes pour les boucles

	void setTemperature(double var_temperature);
	void setChampB(double var_champB);

	//Fait changer de sens un spin du système selon la méthode métropolis. Une seule itération.
	virtual void etapeMetropolis()=0;
	//Initialise le solide
	virtual void initialisation()=0;

public:
	Solide(unsigned int largeur_var =2, double couplageJ_var =0, double thermostat =300, double champB_var =0) : largeur(largeur_var), couplageJ(couplageJ_var), temperature(thermostat), champB(champB_var)
		{
			kbT = temperature*8.6173303E-5;
			champBmuB = champB*5.7883817555E-5;
			limite = largeur-1;
			srand (time(NULL));
			etapes = 10000.0*largeur;
		}


	~Solide()	{}

	//Fait évoluer la température du système de tmin à tmax sur plusieurs étapes.
	void evolutionThermique(double tmin, double tmax,unsigned int nbEtapes);

	//Fait évoluer la température du système de tmin à tmax sur plusieurs étapes.
	void evolutionMagnetique(double bmin, double bmax,unsigned int nbEtapes);
};

#endif
