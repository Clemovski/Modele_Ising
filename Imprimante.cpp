#include "Imprimante.h"
#include <fstream>
#include <string>


//Définition de l'instance
Imprimante* Imprimante::pInstance;

Imprimante::Imprimante()
{
	nomfichierEcriture = "mesures.txt";
	//Ouverture du fichier
	fichierEcriture.open(nomfichierEcriture.c_str(), ios::out);
	if(!fichierEcriture)
	{
		cout << "Fichier d\'ecriture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichierEcriture << "#Temperature(K)	ChampB(T)	EnergieMoy(eV)	MomentMagMoyen	Cv(J/K)	Ksi" << endl;
}

void Imprimante::chargement(int pourcent)
{
	int nBarres = static_cast<int>((pourcent/5));
	std::cout<<"\r"<<"[";
	for(int i=1; i<=20; i++)	std::cout<<((i<=nBarres)?"=":" ");
	std::cout<<"]" << pourcent<<"%";
	std::cout.flush();
}

Imprimante::~Imprimante()
{
	//On ferme le fichier.
	fichierEcriture.close();
}

void Imprimante::ecrire(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi)
{
	//On écrit les valeurs.
	fichierEcriture << temperature << "	" << champMag << "	" << eMoy << "	" << mMoy << "	" << cv << "	" << ksi << endl;
}

void Imprimante::lire(string nomFichier)
{
//Ouverture du fichier
	fstream fichierLecture;
	fichierLecture.open(nomFichier.c_str(), ios::in);
	if(!fichierLecture)
	{
		cout << "Fichier de lecture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	string champ("");
	double nombre=0.0;
//Lecture
	while(fichierLecture>>champ)
	{
		cout<<champ<<endl;
		fichierLecture>>nombre;
		cout<<nombre<<endl;
	}

//Fermeture du fichier
	fichierLecture.close();

}
