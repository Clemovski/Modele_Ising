#include "Imprimante.h"
#include <fstream>
#include <string>


//Définition de l'instance
Imprimante* Imprimante::pInstance;

Imprimante::Imprimante()
{
	nomFichier = "mesures.txt";
	//Ouverture du fichier
	fichier.open(nomFichier.c_str(), ios::out);
	if(!fichier)
	{
		cout << "Fichier d\'ecriture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichier << "#Temperature(K)	ChampB(T)	EnergieMoy(J)	MomentMagMoyen	Cv(J/K)	Ksi" << endl;
}

void Imprimante::chargement(int pourcent)
{
	std::cout<<"\r"<<pourcent<<"%";
	std::cout.flush();
}

Imprimante::~Imprimante()
{
	//On ferme le fichier.
	fichier.close();
}

void Imprimante::ecrire(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi)
{
	//On écrit les valeurs.
	fichier << temperature << "	" << champMag << "	" << eMoy << "	" << mMoy << "	" << cv << "	" << ksi << endl;
}
