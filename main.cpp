#include "Imprimante.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include <iostream>
#include <map>


int main()
{
	std::map<string, double> parametres = Imprimante::instance()->lire("parametres.txt");

	int largeur = 100;		//Nombre de spins par côté
	double couplageJ = 1E12;	//Hz
	double permeabilite = 5000;	//Permeabilite magnetique relative du materiau
	double champB = 0.0;		//Tesla
	double temperature = 300.0;	//Kelvin

	Solide1D solide(parametres["Largeur"], parametres["CouplageJ"], parametres["Permeabilite"],
		parametres["Temperature"], parametres["ChampB"]);
	solide.evolutionThermique(parametres["Min"], parametres["Max"], 1000);
	//solide.evolutionMagnetique(-5.0, 5.0, 1000);


	return 0;
}
