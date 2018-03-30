#include "Imprimante.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include <iostream>

int main()
{
	int largeur = 100;		//Nombre de spins par côté
	double couplageJ = 100.0;	//Hz
	double champB = 0.0;		//Tesla
	double magneton = 0.000057;	//eV/T Bohr = 0.000057
	double temperature = 1000000.0;	//Kelvin

	Solide2D solide(largeur, couplageJ, magneton, temperature, champB);
	solide.evolutionThermique(1000, 1, 1000);

	return 0;
}
