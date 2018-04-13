#include <map>
#include "Imprimante.h"
#include "SolideFactory.h"


int main()
{
	//On récupère les paramètres qu'on va utiliser pour simuler le système.
	std::map<string, double> parametres = Imprimante::instance()->lire("parametres.txt");

	//Instanciation du solide
	Solide* solide = SolideFactory::instance()->create(parametres["Dimension"], static_cast<int>(parametres["Largeur"]),
							parametres["CouplageJ"], parametres["Temperature"],
							parametres["ChampB"]);

	if(parametres["Dimension"]<1 || parametres["Dimension"]>3)
	{
		Imprimante::instance()->console("Dimension du solide indisponible. Veuillez choisir une dimension entre 1 et 3 dans le fichier parametres.txt");
		return 0;
	}else if(!solide)
	{
		Imprimante::instance()->console("Erreur lors de l'instanciation du Solide.");
		exit(2);
	}

	//Lancement de la simulation.
	switch(static_cast<int>(parametres["Mode"])){
	case 0 :
		solide->evolutionThermique(parametres["Min"], parametres["Max"], 1000);
		Imprimante::instance()->console("");
		break;
	case 1 :
		Imprimante::instance()->console("Etape 1/3");
		solide->evolutionMagnetique(0.0, parametres["Max"], 1000);
		Imprimante::instance()->console("");
		Imprimante::instance()->console("Etape 2/3");
		solide->evolutionMagnetique(parametres["Max"], parametres["Min"], 1000);
		Imprimante::instance()->console("");
		Imprimante::instance()->console("Etape 3/3");
		solide->evolutionMagnetique(parametres["Min"], parametres["Max"], 1000);
		Imprimante::instance()->console("");
		break;
	default :
		Imprimante::instance()->console("Mode non-valide. Veuillez choisir 0 pour évolution thermique ou 1 pour évolution magnétique dans le fichier parametres.txt");
	}

	return 0;
}
