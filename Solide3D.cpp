#include <math.h>	//Pour l'exponentielle
#include "Solide3D.h"

void Solide3D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;
	int j = rand()%largeur;
	int k = rand()%largeur;	//On tire un spin i,j au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((
			(
				element[(i+limite)%largeur][j][k] + element[(i+1)%largeur][j][k]
				+ element[i][(j+limite)%largeur][k] + element[i][(j+1)%largeur][k]
				+ element[i][j][(k+limite)%largeur] + element[i][j][(k+1)%largeur]
			)*couplageJ
		)
		+ champBmuB)*2.0*element[i][j][k];

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i][j][k]*=-1;
		energie += deltaE;
		momentMag += 2*element[i][j][k];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE/kbT) > (rand()/double(RAND_MAX)))
	{
		element[i][j][k]*=-1;
		energie += deltaE;
		momentMag += 2*element[i][j][k];
	}
}




void Solide3D::initialisation()
{
//Remplissage initial
	for(int i=0; i<largeur; i++)
	{
		vector<vector<char>> bufferUn;	//Tableau qu'on accrochera à chaque ligne de element.
		for(int j=0; j<largeur; j++)
		{
			vector<char> bufferDeux;
			for(int k=0; k<largeur; k++)
			{
				bufferDeux.push_back((((rand()/double(RAND_MAX))<0.5)?-1:1) );	//On remplit avec des + ou -1 aléatoirement.
			}
			bufferUn.push_back(bufferDeux);
		}
		element.push_back(bufferUn);
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
			for(int k=0; k<largeur; k++)
			{
			//Calcul de l'énergie.
				energieMag += element[i][j][k];
				energieCoup += element[i][j][k]*(element[(i+1)%largeur][j][k]
								+ element[i][(j+1)%largeur][k]
								+ element[i][j][(k+1)%largeur]);
			}
		}
	}
	momentMag = energieMag;
	energieMag*=champBmuB;
	energieCoup*=couplageJ;

	energie = -(energieCoup+energieMag);
}



