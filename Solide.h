#ifndef _SOLIDE
#define _SOLIDE

class Solide
{
protected:
	unsigned int largeur;	//N
	double couplageJ;	//J
	double champB;		//B
	double magneton;	//µ
	double temperature;	//T = thermostat puisque le système est à l'équilibre. (ensemble canonique)

	double energie;		//E Energie instantannée du solide
	double energieMoy;	//Energie moyenne calculée
	double sigmaEnergie;	//Ecart type de l'énergie calculé

	double momentMag;	//M Moment magnétique instantannée
	double momentMagMoy;	//Moment magnétique moyen calculé
	double sigmaMomentMag;	//Ecart type du moment magnétique calculé

	int etapes;		//Nombre d'étapes pour les boucles

public:
	Solide(unsigned int largeur_var =2, double couplageJ_var =0, double magneton_var =0, double thermostat =300, double champB_var =0)
		: largeur(largeur_var), couplageJ(couplageJ_var), magneton(magneton_var), temperature(thermostat), champB(champB_var)
		{}
	~Solide()	{}
};

#endif
