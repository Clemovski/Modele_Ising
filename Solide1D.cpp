#include <time.h>	//time(NULL) pour initialisation des variables aléatoires
#include <stdlib.h>	//Pour l'utilisation de rand().
#include <math.h>	//Pour l'exponentielle
#include "Solide1D.h"

#include <iostream>

void Solide1D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.
	int i = rand()%largeur;	//On tire un spin i au hasard dans la chaîne.

//Calcul de l'énergie si on pivote le spin.
	deltaE = ((element[(i-1<0?largeur-1:i-1)] + element[(i+1)%largeur])
		*couplageJ*4.135667662/1000000000000000.0)*2.0*element[i]	//Constante de Planck en eV.s
		+ champB*magneton;

//On décide de renverser ou non le spin.
	if(deltaE<0.0)
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];	//Entre un sou que j'ai et un sou que j'ai pas y'a deux sous d'écart.
	}
	else if(exp(-1*deltaE*100000.0/(temperature*8.6173303)) > ((double)rand()/RAND_MAX))	//Nombres en dur = constante de Boltzmann en eV/K
	{
		element[i]*=-1;
		energie += deltaE;
		momentMag += 2*element[i];
	}
}





void Solide1D::initialisation()
{
	srand (time(NULL));

//Remplissage initial
	for(int i=0; i<largeur; i++)	{ element.push_back(((rand()%10)<5)?-1:1); }	//On remplit avec des + ou -1 aléatoirement.

//Calcul des grandeurs initiales
	momentMag = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons
	unsigned int limite = largeur - 1;	//Pour ne pas compter deux fois la première intéraction on observe la chaîne jusqu'à largeur-1.

	for(int i=0; i<limite; i++)
	{
	//Calcul de l'énergie.
		energieMag += element[i];
		energieCoup += element[i]*(element[((i-1)%largeur + largeur) % largeur] + element[(i+1)%largeur]);
	}
	energieMag += element[limite];
	momentMag = energieMag;
	energieMag*=champB*magneton;
	energieCoup*=couplageJ;

	energie = -(energieCoup+energieMag);

//On laisse le système évoluer jusqu'à l'équilibre.
	for(int i=0; i<largeur; i++)	etapeMetropolis();
}





double Solide1D::energieMoyenne(unsigned int etapes)
{
	double moyenne = 0.0;
	for(int i=0; i<etapes; i++)
	{
		etapeMetropolis();
		moyenne += energie;
	}
	return moyenne/etapes;
}




double Solide1D::momentMagMoyen(unsigned int etapes)
{
	double moyenne = 0.0;
	for(int i=0; i<etapes; i++)
	{
		etapeMetropolis();
		moyenne += momentMag;
	}
	return moyenne/etapes;
}




void Solide1D::evolutionThermique(double tmin, double tmax,unsigned int etapes)
{
	double step = (tmax-tmin) / etapes;
//Mise à l'équilibre du système.
	temperature = tmin;
	for(int i=0; i<etapes; i++)	etapeMetropolis();

//Evolution du système.
	for(int i=0; i<etapes; i++)
	{
		etapeMetropolis();
		temperature += step;
	}
}





