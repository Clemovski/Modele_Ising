#include <time.h>	//time(NULL) pour initialisation des variables aléatoires
#include <stdlib.h>	//Pour l'utilisation de rand().
#include <math.h>	//Pour l'exponentielle
#include "Solide1D.h"
#include "Imprimante.h"

#include <iostream>
using namespace std;

void Solide1D::etapeMetropolis()
{
	double deltaE = 0.0;	//Différence d'énergie lorsqu'on retourne un spin particulier.

	for(int i=0; i<largeur; i++)
	{
		//Calcul de l'énergie si on pivote le spin.
		deltaE = (champB + (element[(i-1)%largeur] + element[(i+1)%largeur])*couplageJ)*2.0*element[i];
cout<<"("<<(i-1)%largeur << ";" << (i+1)%largeur<<")";
cout<<(element[i]<0?".":"o")<<" ";
		//On décide de renverser ou non le spin.
		if(deltaE<0.0)
		{
			element[i]*=-1;
			energie += deltaE;
			momentMag += element[i];
		}
		else if(exp(-1*deltaE*100000.0/(temperature*8.6173303)) > (rand()%1))	//Nombres en dur = constante de Boltzmann
		{
			element[i]*=-1;
			energie += deltaE;
			momentMag += element[i];
		}
	}
cout<<endl<<endl;
}

void Solide1D::initialisation()
{
	srand (time(NULL));

//Remplissage initial
	for(int i=0; i<largeur; i++)	{ element.push_back(((rand()%10)<5)?-1:1); }	//On remplit avec des + ou -1 aléatoirement.

//Calcul des grandeurs initiales
	double momentMag = 0.0;
	double energieMag = 0.0;	//Energie due au champ B
	double energieCoup = 0.0;	//Energie due au couplage entre les électrons
	int limitte = largeur - 1;	//Pour ne pas compter deux fois la première intéraction on observe la chaîne jusqu'à largeur-1.

	for(int i=0; i<limitte; i++)
	{
		//Calcul de l'énergie.
		energieMag += element[i];
		energieCoup += element[i]*(element[(i-1)%largeur] + element[(i+1)%largeur]);
	}

	energieMag += element[largeur];
	momentMag = energieMag;
	energieMag*=champB*magneton;
	energieCoup*=couplageJ;

	energie = -(energieCoup+energieMag);

//On laisse le système évoluer jusqu'à l'équilibre.
	for(int i=0; i<10; i++)	etapeMetropolis();

}
