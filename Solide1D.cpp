#include <math.h>	//Pour l'exponentielle et la valeur absolue
#include "Solide1D.h"


void Solide1D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;	//On tire un spin i au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((element[(i+limite)%largeur] + element[(i+1)%largeur])
		*couplageJ*4.135667662E-15)*2.0*element[i]	//Constante de Planck en eV.s
		+ champB*5.7883817555E-5;

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE/kbT) > (rand()/RAND_MAX))
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];
	}
}





void Solide1D::initialisation()
{
//Remplissage initial
	for(int i=0; i<largeur; i++)	{ element.push_back(((rand()/RAND_MAX)<0.5)?-1:1); }	//On remplit avec des + ou -1 aléatoirement.

//Calcul des grandeurs initiales
	momentMag = 0.0;
	energie = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons

	for(int i=0; i<limite; i++)	//Pour ne pas compter deux fois la première intéraction on observe la chaîne jusqu'à largeur-1.
	{
	//Calcul de l'énergie.
		energieMag += element[i];
		energieCoup += element[i]*(element[(i+limite) % largeur] + element[(i+1)%largeur]);
	}
	energieMag += element[limite];	//On rajoute le dernier élément qu'on a pas compté.
	momentMag = energieMag;
	energieMag*=champB*5.7883817555E-5;
	energieCoup*=couplageJ*4.135667662E-15;

	energie = -(energieCoup+energieMag);
}









