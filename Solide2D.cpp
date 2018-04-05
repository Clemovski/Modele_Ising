#include <time.h>	//time(NULL) pour initialisation des variables aléatoires
#include <stdlib.h>	//Pour l'utilisation de rand().
#include <math.h>	//Pour l'exponentielle
#include <iostream>	//Chargement
#include "Solide2D.h"
#include "Imprimante.h"	//Pour écrire les données dans un fichier.


void Solide2D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;
	int j = rand()%largeur;	//On tire un spin i,j au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((element[(i+limite)%largeur][j] + element[(i+1)%largeur][j]
			+ element[i][(j+limite)%largeur] + element[i][(j+1)%largeur])
		*couplageJ*4.135667662E-15)*2.0*element[i][j]	//Constante de Planck en eV.s
		+ champB*magneton;

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i][j]*=-1;
		energie += deltaE;
		momentMag += 2*element[i][j];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE/kbT) > ((double)rand()/RAND_MAX))
	{
		element[i][j]*=-1;
		energie += deltaE;
		momentMag += 2*element[i][j];
	}
}





void Solide2D::initialisation()
{
//Remplissage initial
	for(int i=0; i<largeur; i++)
	{
		vector<char> buffer;	//Tableau qu'on accrochera à chaque ligne de element.
		for(int j=0; j<largeur; j++)
		{
			buffer.push_back((((rand()/RAND_MAX)<0.5)?-1:1) );	//On remplit avec des + ou -1 aléatoirement.
		}
		element.push_back(buffer);
	}

//Calcul des grandeurs initiales
	momentMag = 0.0;
	energie = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons

	for(int i=0; i<limite; i++)	//Pour ne pas compter deux fois la première intéraction on observe la chaîne jusqu'à largeur-1.
	{
		for(int j=0; j<limite; j++)
		{
		//Calcul de l'énergie.
			energieMag += element[i][j];
			energieCoup += element[i][j]*(element[i][(j+limite) % largeur] + element[i][(j+1)%largeur]
							+ element[(i+limite) % largeur][j] + element[(i+1)%largeur][j]);
		}
	}

	energieMag += element[limite][limite];	//On rajoute le dernier élément qu'on a pas compté.
	momentMag = energieMag;
	energieMag*=champB*magneton;
	energieCoup*=couplageJ*4.135667662E-15;

	energie = -(energieCoup+energieMag);
}






void Solide2D::evolutionThermique(double tmin, double tmax,unsigned int nbEtapes=0)
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
		for(int j=0; j<etapes; j++)	etapeMetropolis();


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
			, sigmaEnergie/(temperature*kbT)
			, sigmaMomentMag/(temperature*kbT));

		setTemperature(temperature + step);

		Imprimante::instance()->chargement(int(100*(i+1)/nbEtapes));
	}
}





