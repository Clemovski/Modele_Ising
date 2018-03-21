#include "Imprimante.h"
#include "Solide1D.h"
#include <iostream>

int main()
{
	int largeur = 10;		//Nombre de spins par côté
	double couplageJ = 100.0;	//Hz
	double champB = 0.0;		//Tesla
	double magneton = 0.0;		//eV/T Bohr = 0.000057
	double temperature = 100000.0;	//Kelvin

	Solide1D solide(largeur, couplageJ, magneton, temperature, champB);

	return 0;
}
