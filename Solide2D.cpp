#include <math.h>	//Pour l'exponentielle
#include "Solide2D.h"


void Solide2D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;
	int j = rand()%largeur;	//On tire un spin i,j au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((
			(
				element[(i+limite)%largeur][j] + element[(i+1)%largeur][j]
				+ element[i][(j+limite)%largeur] + element[i][(j+1)%largeur]
			)*couplageJ
		)
		+ champBmuB)*2.0*element[i][j];

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i][j]*=-1;
		energie += deltaE;
		momentMag += 2*element[i][j];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE/kbT) > (rand()/double(RAND_MAX)))
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
			buffer.push_back((((rand()/double(RAND_MAX))<0.5)?-1:1) );	//On remplit avec des + ou -1 aléatoirement.
		}
		element.push_back(buffer);
	}

//Calcul des grandeurs initiales
	momentMag = 0.0;
	energie = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons

	for(int i=0; i<largeur; i++)
	{
		for(int j=0; j<largeur; j++)
		{
		//Calcul de l'énergie.
			energieMag += element[i][j];
			energieCoup += element[i][j]*(element[(i+1)%largeur][j] + element[i][(j+1)%largeur]);
		}
	}
	momentMag = energieMag;
	energieMag*=champBmuB;
	energieCoup*=couplageJ;

	energie = -(energieCoup+energieMag);
}



