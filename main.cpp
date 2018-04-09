#include "Imprimante.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include <iostream>

int main()
{
	int largeur = 100;		//Nombre de spins par côté
	double couplageJ = 1E12;	//Hz
	double permeabilite = 5000;	//Permeabilite magnetique relative du materiau
	double champB = 0.0;		//Tesla
	double temperature = 300.0;	//Kelvin

	Solide1D solide(largeur, couplageJ, permeabilite, temperature, champB);
	//solide.evolutionThermique(10000.0, 1.0, 1000);
	//solide.evolutionMagnetique(-5.0, 5.0, 1000);

	Imprimante::instance()->lire("parametres.txt");

	return 0;
}
