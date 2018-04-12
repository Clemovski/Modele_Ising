#include "Imprimante.h"
#include "Solide1D.h"
#include "Solide2D.h"
#include <iostream>
#include <map>


int main()
{
	//On récupère les paramètres qu'on va utiliser pour simuler le système.
	std::map<string, double> parametres = Imprimante::instance()->lire("parametres.txt");

	Solide1D solide(parametres["Largeur"], parametres["CouplageJ"], parametres["Permeabilite"],
			parametres["Temperature"], parametres["ChampB"]);
	/*Solide2D solide(parametres["Largeur"], parametres["CouplageJ"], parametres["Permeabilite"],
			parametres["Temperature"], parametres["ChampB"]);*/

	//Lancement de la simulation.
	switch(static_cast<int>(parametres["Mode"])){
	case 0 :
		solide.evolutionThermique(parametres["Min"], parametres["Max"], 1000);
		break;
	case 1 :
		solide.evolutionMagnetique(parametres["Min"], parametres["Max"], 1000);
		break;
	}

	return 0;
}
