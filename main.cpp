#include "Imprimante.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include <iostream>

int main()
{
	int largeur = 100;		//Nombre de spins par côté
	double couplageJ = 100.0;	//Hz
	double champB = 0.0;		//Tesla
	double temperature = 1000000.0;	//Kelvin

	Solide2D solide(largeur, couplageJ, temperature, champB);
	solide.evolutionThermique(1000, 1, 1000);

	return 0;
}
