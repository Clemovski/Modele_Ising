#include "Imprimante.h"
#include <fstream>
#include <string>

void Imprimante::ecrire()
{/*
	//Ouverture du fichier
	fstream fichier;
	fichier.open(nomFichier.c_str(), ios::out);
	if(!fichier)
	{
		cout << "Fichier d\'ecriture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les valeurs.
	int longeur = valeurs.size();
	for(int i = 0; i<longeur; i++)
	{
		fichier << valeurs[i] << endl;
	}

	//On ferme le fichier.
	fichier.close();*/
}

void Imprimante::lire()
{/*
	//Ouverture du fichier.
	fstream fichier;
	fichier.open(nomFichier.c_str(), ios::in);
	if(!fichier)
	{
		cout << "Fichier de lecture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//Lecture
	float nombre = 0;
	while(!fichier.eof())
	{
		fichier >> nombre;
		valeursLues.push_back(nombre);
	}

	//Fermeture du fchier.
	fichier.close();*/
}
