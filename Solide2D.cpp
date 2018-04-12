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
		+ champB*permeabilite;

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
}



