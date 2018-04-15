#include <cmath>	//Pour l'exponentielle et la valeur absolue
#include "Solide1D.h"
#include "Imprimante.h" //Pour ecrirePositionsSpin()


void Solide1D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;	//On tire un spin i au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((
			(element[(i+limite)%largeur] + element[(i+1)%largeur])*couplageJ
		)
		+ champBmuB)*2.0*element[i];

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE/kbT) > (rand()/double(RAND_MAX)))
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];
	}
}





void Solide1D::initialisation()
{
//Remplissage initial
	for(unsigned int i=0; i<largeur; i++)	{ element.push_back(((rand()/double(RAND_MAX))<0.5)?-1:1); }	//On remplit avec des + ou -1 aléatoirement.

//Calcul des grandeurs initiales
	momentMag = 0.0;
	energie = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons

	for(unsigned int i=0; i<largeur; i++)
	{
	//Calcul de l'énergie.
		energieMag += element[i];
		energieCoup += element[i]*element[(i+1)%largeur];
	}
	momentMag = energieMag;
	energieMag*=champBmuB;
	energieCoup*=couplageJ;

	energie = -(energieCoup+energieMag);
}





void Solide1D::ecrirePositionsSpins()
{
    for(unsigned int x=0; x<largeur; x++){
        if(element[x]>0)  Imprimante::instance()->ecrirePosition(x);
        //Eventuellement else Ecrire dans le fichier down.
    }
}
