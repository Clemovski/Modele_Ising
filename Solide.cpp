#include <stdlib.h> //Pour l'utilisation de rand().
#include <cmath>    //Pour abs()
#include <string>   //Pour setFichierWeiss().
#include <stdio.h>  //Pour convertir int en string
#include "Solide.h"
#include "Imprimante.h"	//Pour écrire les données dans un fichier.

//Change la température et tout ce qui va avec.
void Solide::setTemperature(double var_temperature)
{
	temperature = var_temperature;
	kbT = temperature*8.6173303E-5;	//Constante de Boltzmann en eV/K
}


//Change le champ Magnétique et tout ce qui va avec.
void Solide::setChampB(double var_champB)
{
	champB = var_champB;
	champBmuB = champB*5.7883817555E-5;	//Magneton de Bohr en eV/T
}


//Fait évoluer le système de Tmin à Tmax et enregistre les données dans mesures.txt
void Solide::evolutionThermique(double tmin, double tmax,unsigned int nbEtapes)
{
	if(nbEtapes==0)	nbEtapes = abs(tmax-tmin);
	double step = (tmax-tmin) / nbEtapes;
	setTemperature(tmin);

//Evolution du système.
	for(unsigned int i=0; i<nbEtapes; i++)
	{
		energieMoy = sigmaEnergie = momentMagMoy = sigmaMomentMag = 0.0;

	//Mise à l'équilibre du système.
		//for(int j=0; j<etapes; j++)	etapeMetropolis();

	//Calcul des grandeurs utiles.
		for(unsigned int j=0; j<etapes; j++)
		{
			energieMoy += energie;
			sigmaEnergie += energie*energie;	//Calcule <E²> pour l'instant.
			momentMagMoy += momentMag;
			sigmaMomentMag += momentMag*momentMag;	//Calcule <M²>
			etapeMetropolis();
		}

		energieMoy = energieMoy/etapes;
		momentMagMoy = momentMagMoy / etapes;
		sigmaEnergie /= etapes;
		sigmaMomentMag /= etapes;
		sigmaEnergie -= energieMoy*energieMoy;
		sigmaMomentMag -= momentMagMoy*momentMagMoy;

	//Ecriture des valeurs moyennes, de Cv et ksi dans un fichier.
		Imprimante::instance()->ecrireMesures(temperature, champB, energieMoy, momentMagMoy
			, abs(sigmaEnergie/(temperature*kbT))
			, abs(sigmaMomentMag/(temperature*kbT)));

		setTemperature(temperature+step);

		Imprimante::instance()->chargement(int(100*(i+1)/nbEtapes));
	}
}






//Fait évoluer le système de Bmin à Bmax et enregistre les données dans mesures.txt
void Solide::evolutionMagnetique(double bmin, double bmax,unsigned int nbEtapes)
{
	if(nbEtapes==0)	nbEtapes = abs(bmax-bmin) * 100.0;
	double step = (bmax-bmin) / nbEtapes;
	setChampB(bmin);

//Evolution du système.
	for(unsigned int i=0; i<nbEtapes; i++)
	{
		energieMoy = sigmaEnergie = momentMagMoy = sigmaMomentMag = 0.0;

	//Mise à l'équilibre du système.
		//for(int j=0; j<etapes; j++)	etapeMetropolis();

	//Calcul des grandeurs utiles.
		for(unsigned int j=0; j<etapes; j++)
		{
			energieMoy += energie;
			sigmaEnergie += energie*energie;
			momentMagMoy += momentMag;
			sigmaMomentMag += momentMag*momentMag;
			etapeMetropolis();
		}

		energieMoy = energieMoy/etapes;
		momentMagMoy = momentMagMoy / etapes;
		sigmaEnergie /= etapes;
		sigmaMomentMag /= etapes;
		sigmaEnergie -= energieMoy*energieMoy;
		sigmaMomentMag -= momentMagMoy*momentMagMoy;

	//Ecriture des valeurs moyennes, de Cv et xi dans un fichier.
		Imprimante::instance()->ecrireMesures(temperature, champB, energieMoy, momentMagMoy
			, abs(sigmaEnergie/(temperature*kbT))
			, abs(sigmaMomentMag/(temperature*kbT)));

        if(i%10==0)
        {
            //Ecriture de la position des spins.
            ecrirePositionsSpins();
            //On crée un nouveau fichier Weiss.
            Imprimante::instance()->nextFichierWeiss();
        }

		setChampB(champB+step);

		Imprimante::instance()->chargement(int(100*(i+1)/nbEtapes));
	}
}

