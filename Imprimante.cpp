#include <iomanip>
#include <cstdlib>
#include "Imprimante.h"


//Définition de l'instance
Imprimante* Imprimante::pInstance;

Imprimante::Imprimante()
{
//Initialisation du fichier mesures.txt
	nomFichierMesures = "mesures.txt";

	//Ouverture du fichier
	fichierMesures.open(nomFichierMesures.c_str(), ios::out);
	if(!fichierMesures)
	{
		cout << "Fichier '" << nomFichierMesures << "' (mesures) foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichierMesures << setw(20) << "#Temperature(K)" << "	"
	 << setw(20) << "ChampB(T)" << "	"
	 << setw(20) << "EnergieMoy(eV)" << "	"
	 << setw(20) << "MomentMagMoyen" << "	"
	 << setw(20) << "Cv(eV/K)" << "	"
	 << setw(20) << "Ksi" << endl;


//Initialisation du fichier Weiss.txt
    compteurWeiss = 0;
	nomFichierWeiss = "Weiss.txt";

	//Ouverture du fichier
	fichierWeiss.open(nomFichierWeiss.c_str(), ios::out);
	if(!fichierWeiss)
	{
		cout << "Fichier '" << nomFichierWeiss << "' (Weiss) foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichierWeiss << setw(20) << "#x" << "	"
	 << setw(20) << "y" << "	"
	 << setw(20) << "z" << endl;
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
//On ferme les fichier.
	fichierMesures.close();
    fichierWeiss.close();
}






void Imprimante::ecrireMesures(double temperature, double champMag, double eMoy, double mMoy,double cv, double ksi)
{
	//On écrit les valeurs.
	fichierMesures << setw(20) << temperature << "	" << setw(20) << champMag << "	" << setw(20) << eMoy << "	" << setw(20) << mMoy << "	" << setw(20) << cv << "	" << setw(20) << ksi << endl;
}






map<string, double> Imprimante::lire(string nomFichier)
{
//Ouverture du fichier
	fstream fichierLecture;
	fichierLecture.open(nomFichier.c_str(), ios::in);
	if(!fichierLecture)
	{
		cout << "Pas de fichier '" << nomFichier << "'. Consultez de fichier LisezMoi.txt si besoin pour le créer." << endl;
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





void Imprimante::setFichierMesures(string nouveauFichier)
{
	fichierMesures.close();
	nomFichierMesures = nouveauFichier;

	//Ouverture du fichier
	fichierMesures.open(nomFichierMesures.c_str(), ios::out);
	if(!fichierMesures)
	{
		cout << "Fichier '" << nouveauFichier << "' (mesures) foireux. Abanonnez le navire !" << endl;
		exit(1);
	}

	//On écrit les entêtes.
	fichierMesures << setw(20) << "#Temperature(K)" << "	"
	 << setw(20) << "ChampB(T)" << "	"
	 << setw(20) << "EnergieMoy(eV)" << "	"
	 << setw(20) << "MomentMagMoyen" << "	"
	 << setw(20) << "Cv(eV/K)" << "	"
	 << setw(20) << "Ksi" << endl;
}





void Imprimante::nextFichierWeiss()
{
    fichierWeiss << endl << endl;
}





void Imprimante::ecrirePosition(unsigned int x, unsigned int y, unsigned int z)
{
    fichierWeiss << setw(20) << x << "	"
	 << setw(20) << y << "	"
	 << setw(20) << z << endl;
}





void Imprimante::ecrirePosition(unsigned int x, unsigned int y)
{
    fichierWeiss << setw(20) << x << "	"
	 << setw(20) << y << endl;
}





void Imprimante::ecrirePosition(unsigned int x)
{
    fichierWeiss << setw(20) << x << endl;
}
