#include "Imprimante.h"
#include <iomanip>


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
	fichierEcriture << setw(20) << "#Temperature(K)" << "	"
	 << setw(20) << "ChampB(T)" << "	"
	 << setw(20) << "EnergieMoy(eV)" << "	"
	 << setw(20) << "MomentMagMoyen" << "	"
	 << setw(20) << "Cv(eV/K)" << "	"
	 << setw(20) << "Ksi" << endl;
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
	fichierEcriture << setw(20) << temperature << "	" << setw(20) << champMag << "	" << setw(20) << eMoy << "	" << setw(20) << mMoy << "	" << setw(20) << cv << "	" << setw(20) << ksi << endl;
}

map<string, double> Imprimante::lire(string nomFichier)
{
//Ouverture du fichier
	fstream fichierLecture;
	fichierLecture.open(nomFichier.c_str(), ios::in);
	if(!fichierLecture)
	{
		cout << "Fichier de lecture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	map<string, double> parametres;

	string champ("");
	double nombre=0.0;
//Lecture
	while(fichierLecture>>champ)
	{
		fichierLecture>>nombre;
		parametres.insert ( std::pair<string, double>(champ,nombre) );
	}

//Fermeture du fichier
	fichierLecture.close();

	return parametres;

}




void Imprimante::setFichierEcriture(string nouveauFichier)
{
	fichierEcriture.close();
	nomfichierEcriture = nouveauFichier;

	//Ouverture du fichier
	fichierEcriture.open(nomfichierEcriture.c_str(), ios::out);
	if(!fichierEcriture)
	{
		cout << "Fichier d\'ecriture foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichierEcriture << setw(20) << "#Temperature(K)" << "	"
	 << setw(20) << "ChampB(T)" << "	"
	 << setw(20) << "EnergieMoy(eV)" << "	"
	 << setw(20) << "MomentMagMoyen" << "	"
	 << setw(20) << "Cv(eV/K)" << "	"
	 << setw(20) << "Ksi" << endl;
}
