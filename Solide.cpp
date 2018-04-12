#include <stdlib.h>	//Pour l'utilisation de rand().
#include "Solide.h"
#include "Imprimante.h"	//Pour écrire les données dans un fichier.
#include <math.h>	//Pour la valeur absolue



//Change la température et tout ce qui va avec.
void Solide::setTemperature(double var_temperature)
	{
		temperature = var_temperature;
		kbT = temperature*8.6173303E-5;
	}





//Fait évoluer le système de Tmin à Tmax et enregistre les données dans mesures.txt
void Solide::evolutionThermique(double tmin, double tmax,unsigned int nbEtapes)
{
	if(nbEtapes==0)	nbEtapes = abs(tmax-tmin);
	double step = (tmax-tmin) / nbEtapes;
	setTemperature(tmin);

//Evolution du système.
	for(int i=0; i<nbEtapes; i++)
	{
		energieMoy = 0.0;
		sigmaEnergie = 0.0;
		momentMagMoy = 0.0;
		sigmaMomentMag = 0.0;

	//Mise à l'équilibre du système.
		//for(int j=0; j<etapes; j++)	etapeMetropolis();

	//Calcul des grandeurs utiles.
		for(int j=0; j<etapes; j++)
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
		Imprimante::instance()->ecrire(temperature, champB, energieMoy, momentMagMoy
			, abs(sigmaEnergie/(temperature*kbT))
			, abs(sigmaMomentMag/(temperature*kbT)));

		setTemperature(temperature+step);

		Imprimante::instance()->chargement(int(100*(i+1)/nbEtapes));
	}
}






//Fait évoluer le système de Bmin à Bmax et enregistre les données dans mesures.txt
void Solide::evolutionMagnetique(double bmin, double bmax,unsigned int nbEtapes)
{
	if(nbEtapes==0)	nbEtapes = abs(bmax-bmin);
	double step = (bmax-bmin) / nbEtapes;
	champB = bmin;

//Evolution du système.
	for(int i=0; i<nbEtapes; i++)
	{
		energieMoy = 0.0;
		sigmaEnergie = 0.0;
		momentMagMoy = 0.0;
		sigmaMomentMag = 0.0;

	//Mise à l'équilibre du système.
		//for(int j=0; j<etapes; j++)	etapeMetropolis();

	//Calcul des grandeurs utiles.
		for(int j=0; j<etapes; j++)
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

	//Ecriture des valeurs moyennes, de Cv et ksi dans un fichier.
		Imprimante::instance()->ecrire(temperature, champB, energieMoy, momentMagMoy
			, abs(sigmaEnergie/(temperature*kbT))
			, abs(sigmaMomentMag/(temperature*kbT)));

		champB+=step;

		Imprimante::instance()->chargement(int(100*(i+1)/nbEtapes));
	}
}
